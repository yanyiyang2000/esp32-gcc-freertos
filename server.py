import socket

def main():
    host        = "192.168.1.123"   # server IPv4 address
    port        = 12345             # server port number
    buffer_size = 1024              # buffer size in bytes
    timeout     = 1                 # timeout in seconds

    # Establish TCP connection with client
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)
    print(f"Listening on {host}:{port}")
    client_socket, client_address = server_socket.accept()
    client_socket.settimeout(timeout)
    print(f"Connection from {client_address[0]}:{client_address[1]}")

    # Send message to and then receive reply from the client
    try:
        message_out = input("Enter message: ").strip()
        message_in  = b""
        client_socket.sendall(message_out.encode("utf-8"))
        while True:
            try:
                chunk = client_socket.recv(buffer_size)
                if not chunk:
                    break
                message_in += chunk
            except socket.timeout:
                print("Timeout.")
                break
        if message_in:
            print(f"{message_in}")

    except KeyboardInterrupt:
        pass

    finally:
        client_socket.close()
        server_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    main()
