#Simple get request to get large amounts of data
#See https://code.activestate.com/recipes/408859-socketrecv-three-ways-to-turn-it-into-recvall/
#see https://www.geeks3d.com/hacklab/20190110/python-3-simple-http-request-with-the-socket-module/

import socket

host = "gaia.cs.umass.edu"
port = 80

#set up socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  

#connect to the server
client.connect((host,port)) 

#Send GET request
request = "GET /wireshark-labs/HTTP-wireshark-file3.html HTTP/1.1\r\nHost:gaia.cs.umass.edu\r\n\r\n"
client.send(request.encode())

#loop through recv until all data is received from the server
#We assume a socket disconnect when data is done being transfered
total_data = []
while(True):
    data = client.recv(4096)
    if not data: break
    total_data.append(data)


response = b''.join(total_data)


#print response
print(response.decode("UTF-8"))