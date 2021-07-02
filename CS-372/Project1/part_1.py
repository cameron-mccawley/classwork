#Simple get request to get small amounts of data
#see https://www.geeks3d.com/hacklab/20190110/python-3-simple-http-request-with-the-socket-module/

import socket

host = "gaia.cs.umass.edu"
port = 80

#set up socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  

#connect to the server
client.connect((host,port)) 

#Send GET request
request = "GET /wireshark-labs/HTTP-wireshark-file1.html HTTP/1.1\r\nHost:gaia.cs.umass.edu\r\n\r\n"
client.send(request.encode())

response = client.recv(4096)  

#print response
print(response.decode("UTF-8"))