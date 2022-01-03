import socket


class Client:
    def __init__(self, gui):
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server = "localhost"
        port = 27015
        self.gui = gui
        self.addr = (server, port)
        self.connect()

    def connect(self):
        try:
            self.client.connect(self.addr)
            print("Connected")
        except socket.error:
            print("Error")

    def disconnect(self):
        """
        Disconnect from the server
        """
        try:
            self.client.close()
            print("Disconnected")
        except socket.error:
            pass

    def get(self):
        """
        Get message from server
        :return: bytes
        """
        try:
            return self.client.recv(2048)
        except socket.error:
            return b"error"

    def send(self, data):
        """
        Send bytes data to server
        :param data: bytes
        """
        try:
            self.client.send(data)
        except socket.error as e:
            print(e)

    def receive(self):
        """
        Get messages from server
        """
        while True:
            try:
                message = str(self.get(), encoding="UTF-8")
                if message == "error":
                    self.gui.receive_event("Error")
                    print("Error")
                    return
                print("CLIENT message:", message)
                self.gui.receive_event(message)
            except socket.error:
                print("Stop receiving")
                return
            except Exception as e:
                print(e)
                return
