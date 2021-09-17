import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.stream.Collectors;
import java.net.URL;
import javax.net.ssl.HttpsURLConnection;

public class Utils {
    // Performs generic HTTPS GET requests; returns JSON as a String
    public static String httpsGetRequest(String urlString) throws IOException{
        URL url = new URL(urlString);
        HttpsURLConnection connection = (HttpsURLConnection) url.openConnection();
        connection.setRequestMethod("GET");
        connection.setRequestProperty("Accept", "application/json");

        if (connection.getResponseCode() != 200) {
            System.out.println("Unsuccessful GET request: " + connection.getResponseCode());
            System.out.println(connection.getResponseMessage());
        }
        String jsonResponse = new BufferedReader(
            new InputStreamReader(connection.getInputStream()))
                .lines().collect(Collectors.joining());

        return jsonResponse;
    }
}
