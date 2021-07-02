# Sources:

# https://realpython.com/python-sockets/
# https://docs.python.org/3/library/socket.html
# https://stackoverflow.com/questions/7749341/basic-python-client-socket-example
# https://www.w3schools.com/python/ref_string_strip.asp


from socket import *

IP = 'localhost'
PORT = 1337

#Initialize socket and connect to server
client_soc = socket(AF_INET, SOCK_STREAM)
client_soc.connect((IP, PORT))
print("Connected to: " + IP + "on port: " + str(PORT))

print("Waiting for message...")

#Get first message
client_data = input(">")

#Send first message
client_soc.send(client_data.encode())
print("Type /q to quit")

#While connection is not terminated, send data
while(True):
    #Receive server message
    server_data = client_soc.recv(1024).decode()

    print(server_data)

    #Get input from user
    print("Enter message to send...")
    client_data = input(">")

    if(client_data.strip() == "/q"):
        break

    #Send message
    client_soc.send(client_data.encode())

#Close connection
client_soc.close()



