#Cameron McCawley

#SOURCES USED:
# https://stackoverflow.com/questions/9371114/check-if-list-of-objects-contain-an-object-with-a-certain-attribute-value
# https://docs.python.org/3/library/copy.html
# https://www.geeksforgeeks.org/copy-python-deep-copy-shallow-copy/
# https://www.geeksforgeeks.org/reliable-data-transfer-rdt-1-0/
# https://www.pythoncheatsheet.org/#Lists
# http://www2.ic.uff.br/~michael/kr1999/3-transport/3_040-principles_rdt.htm
# Chapter 3 from Kurose and Ross, Computer Networking: A Top-Down Approach, 7th Edition,Pearson
# Ed discussion
# Help from office hours

from segment import Segment
from unreliable import *
import copy

# #################################################################################################################### #
# RDTLayer                                                                                                             #
#                                                                                                                      #
# Description:                                                                                                         #
# The reliable data transfer (RDT) layer is used as a communication layer to resolve issues over an unreliable         #
# channel.                                                                                                             #
#                                                                                                                      #
#                                                                                                                      #
# Notes:                                                                                                               #
# This file is meant to be changed.                                                                                    #
#                                                                                                                      #
#                                                                                                                      #
# #################################################################################################################### #


class RDTLayer(object):
    # ################################################################################################################ #
    # Class Scope Variables                                                                                            #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    DATA_LENGTH = 4 # in characters                     # The length of the string data that will be sent per packet...
    FLOW_CONTROL_WIN_SIZE = 15 # in characters          # Receive window size for flow-control
    sendChannel = None
    receiveChannel = None

    # ################################################################################################################ #
    # __init__()                                                                                                       #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def __init__(self):
        self.sendChannel = None
        self.receiveChannel = None
        self.dataToSend = ''
        self.currentIteration = 0
        # Add items as needed
        self.seqnum = 0
        self.acknum = 0
        self.countSegmentTimeouts = 0
        self.dataReceived = ''
        self.segList = []
        self.tempReceivedSegments = []

    def updateSegs(self):
        for tempSeg in self.tempReceivedSegments:
            if (self.acknum == tempSeg.seqnum):
                self.dataReceived = self.dataReceived + tempSeg.payload
                self.acknum = self.acknum + self.DATA_LENGTH
                self.tempReceivedSegments.remove(tempSeg)
                #call self until no out of order segments
                self.updateSegs() 
                break

    # ################################################################################################################ #
    # setSendChannel()                                                                                                 #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to set the unreliable sending lower-layer channel                                                 #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def setSendChannel(self, channel):
        self.sendChannel = channel

    # ################################################################################################################ #
    # setReceiveChannel()                                                                                              #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to set the unreliable receiving lower-layer channel                                               #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def setReceiveChannel(self, channel):
        self.receiveChannel = channel

    # ################################################################################################################ #
    # setDataToSend()                                                                                                  #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to set the string data to send                                                                    #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def setDataToSend(self,data):
        self.dataToSend = data

    # ################################################################################################################ #
    # getDataReceived()                                                                                                #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to get the currently received and buffered string data, in order                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def getDataReceived(self):
        # ############################################################################################################ #
        # Identify the data that has been received...
        # ############################################################################################################ #
        return self.dataReceived

    # ################################################################################################################ #
    # processData()                                                                                                    #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # "timeslice". Called by main once per iteration                                                                   #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def processData(self):
        self.currentIteration += 1
        self.processSend()
        self.processReceiveAndSendRespond()


    # ################################################################################################################ #
    # processSend()                                                                                                    #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Manages Segment sending tasks                                                                                    #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def processSend(self):
        # ############################################################################################################ #
        for seg in self.segList:
            if (self.currentIteration - seg.getStartIteration() > 5):
                #Timed out, so resend
                self.countSegmentTimeouts = self.countSegmentTimeouts + 1
                seg.setStartIteration(self.currentIteration)
                # https://docs.python.org/3/library/copy.html
                self.sendChannel.send(copy.copy(seg))

        # You should pipeline segments to fit the flow-control window
        # The flow-control window is the constant RDTLayer.FLOW_CONTROL_WIN_SIZE
        # The maximum data that you can send in a segment is RDTLayer.DATA_LENGTH
        # These constants are given in # characters

        # Somewhere in here you will be creating data segments to send.
        # The data is just part of the entire string that you are trying to send.
        # The seqnum is the sequence number for the segment (in character number, not bytes)

        while ((self.seqnum + self.DATA_LENGTH) < (self.acknum + self.FLOW_CONTROL_WIN_SIZE)):
            if (self.seqnum < len(self.dataToSend)):
                seg = Segment()
                data = self.dataToSend[self.seqnum:self.seqnum+self.DATA_LENGTH]
                seg.setData(self.seqnum, data)
                # using this for timeouts
                seg.setStartIteration(self.currentIteration)          
                self.seqnum = self.seqnum + self.DATA_LENGTH
                print("Sending segment: ", seg.to_string())
                # https://docs.python.org/3/library/copy.html
                self.sendChannel.send(copy.copy(seg))
                self.segList.append(seg)
            else:
                #done sending data, break
                break


        
    # ################################################################################################################ #
    # processReceive()                                                                                                 #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Manages Segment receive tasks                                                                                    #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def processReceiveAndSendRespond(self):

        # This call returns a list of incoming segments (see Segment class)...
        listIncomingSegments = self.receiveChannel.receive()
        sendAck = False

        # ############################################################################################################ #
        # What segments have been received?
        # How will you get them back in order?
        # This is where a majority of your logic will be implemented
        for recv in listIncomingSegments:
            if (recv.seqnum == self.acknum):
                #Is packet corrupt?
                if (recv.checkChecksum()):
                    self.dataReceived = self.dataReceived + recv.payload
                    # update the next expexted seg
                    self.acknum = self.acknum + self.DATA_LENGTH
                    self.updateSegs()
                    sendAck = True
                
            elif (recv.seqnum == -1):
                #This is an ack for our ack, so dont send one back
                sendAck = False
                
                # Checking for duplicate acks
                # https://stackoverflow.com/questions/9371114/check-if-list-of-objects-contain-an-object-with-a-certain-attribute-value
                self.segList[:] = [tempSeg for tempSeg in self.segList if not (tempSeg.seqnum < recv.acknum)]
                self.acknum = recv.acknum

            #out of order, so save it
            elif (recv.seqnum > self.acknum):
                if (recv.checkChecksum()): #is it in the list?
                    # https://stackoverflow.com/questions/9371114/check-if-list-of-objects-contain-an-object-with-a-certain-attribute-value
                    if(not any(tempSeg.seqnum == recv.seqnum for tempSeg in self.tempReceivedSegments)):
                        self.tempReceivedSegments.append(recv)
                    sendAck = True
            else:
                sendAck = True


        # ############################################################################################################ #
        # How do you respond to what you have received?
        # How can you tell data segments apart from ack segemnts?

        # Somewhere in here you will be setting the contents of the ack segments to send.
        # The goal is to employ cumulative ack, just like TCP does...
        if (sendAck):
            ack = Segment()
            ack.setAck(self.acknum)

            # Use the unreliable sendChannel to send the ack packet
            print("Sending ack: ", ack.to_string())
            self.sendChannel.send(ack)