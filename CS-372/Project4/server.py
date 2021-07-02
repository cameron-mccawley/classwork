# Sources:

# https://realpython.com/python-sockets/
# https://docs.python.org/3/library/socket.html
# https://stackoverflow.com/questions/7749341/basic-python-client-socket-example
# https://www.w3schools.com/python/ref_string_strip.asp


from socket import *

IP = 'localhost'
PORT = 1337

#Initialize socket
server_soc = socket(AF_INET, SOCK_STREAM)
server_soc.bind((IP, PORT))

#Listen for connection
print("Sever listening on: " + IP + " on port: " + str(PORT))
server_soc.listen(2)

#Accept incoming connection
conn, addr = server_soc.accept()
print("Connected by " + str(addr))
print("Waiting for message...")

client_data = conn.recv(1024).decode()
print(str(client_data))
print("Type /q to quit")

#Loop until connection closes
while(True):
    #Send data from server to client
    server_data = input(">")
    conn.send(server_data.encode())

    #Get data from client
    client_data = conn.recv(1024).decode()
    if not client_data:
        break
    print(str(client_data))

#Close the connection
conn.close()
    