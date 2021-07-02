#Basic HTTP server
#See https://www.codementor.io/@joaojonesventura/building-a-basic-http-server-from-scratch-in-python-1cedkg0842
#See https://realpython.com/python-sockets/

import socket

ip = '127.0.0.1'
port = 8080

# Create socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((ip, port))
s.listen(1)

print('Listening on port ' + str(port) + " ...")

#The response we are going to be sending
data = "HTTP/1.1 200 OK\r\n"\
 "Content-Type: text/html; charset=UTF-8\r\n\r\n"\
 "<html>Congratulations! You've downloaded the first Wireshark lab file!</html>\r\n"

while True:    
    #wait for connection
    conn, addr = s.accept()

    #get the client request
    request = conn.recv(1024).decode()
    print(request)

    #send HTTP response
    conn.sendall(data.encode())
    conn.close()

#close socket
s.close()