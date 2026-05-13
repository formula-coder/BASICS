package network;

import java.io.*;
import java.net.*;

public class GameServer {
    private ServerSocket serverSocket;
    private Socket socket;
    private PrintWriter out;
    private BufferedReader in;

    public void start(int port) throws IOException {
        serverSocket = new ServerSocket(port);
        System.out.println("Servidor escuchando en puerto " + port);
        socket = serverSocket.accept();
        System.out.println("Cliente conectado desde: " + socket.getInetAddress());
        out = new PrintWriter(socket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
    }

    public void sendMove(String move) throws IOException {
        out.println(move);
    }

    public String receiveMove() throws IOException {
        return in.readLine();
    }

    public void sendRobotStats(String stats) throws IOException {
        out.println(stats);
    }

    public String receiveRobotStats() throws IOException {
        return in.readLine();
    }

    public void close() throws IOException {
        if (in != null) in.close();
        if (out != null) out.close();
        if (socket != null) socket.close();
        if (serverSocket != null) serverSocket.close();
    }
}
