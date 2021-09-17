import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.util.HashMap;
import java.util.Scanner;

public class CurrencyApi {
    private static String apiKey = "";

    // Retrieves apiKey from txt file
    static {
        File apiKeyFile = new File("lib/apiKey.txt");
        Scanner scanner = null;

        try {
            scanner = new Scanner(apiKeyFile);
            apiKey = scanner.nextLine();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            scanner.close();
        }
    }

    // Retrieves list of currencies by triggering GET request
    protected static HashMap<String,String> getCurrencies() {
        HashMap<String,String> currenciesMap = null;

        // API request
        String urlString = "https://free.currconv.com/api/v7/currencies?apiKey="
            + apiKey;
        String currenciesJson = null;

        try {
            currenciesJson = Utils.httpsGetRequest(urlString);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // JSON parsing
        try {
            JSONObject parsedJson = (JSONObject) new JSONParser().parse(currenciesJson);
            JSONObject results = (JSONObject) parsedJson.get("results");

            currenciesMap = new HashMap<String,String>();

            for (Object result : results.values()) {
                String currencyId = ((JSONObject) result).get("id").toString();
                String currencyName = ((JSONObject) result).get("currencyName").toString();

                currenciesMap.put(currencyName, currencyId);
            }
        } catch (ParseException e) {
            e.printStackTrace();
        }
        
        return currenciesMap;
    }

    // Converts cash value between two currencies; returns converted value as a double
    protected static double convertCurrencies(String currency1, String currency2, Double amount) {
        double result = -1;

        // API request
        String query = currency1 + '_' + currency2;
        String urlString = "https://free.currconv.com/api/v7/convert?q="
            + query + "&compact=ultra&apiKey=" + apiKey;
        String conversionJson = null;

        try {
            conversionJson = Utils.httpsGetRequest(urlString);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // JSON parsing
        try {
            JSONObject parsedJson = (JSONObject) new JSONParser().parse(conversionJson);
            String conversion = String.valueOf(parsedJson.values().iterator().next());
            result = amount * Double.parseDouble(conversion);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        return result;
    }
}
