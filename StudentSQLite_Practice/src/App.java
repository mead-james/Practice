import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
// import java.util.logging.Level;
// import java.util.logging.Logger;

public class App {
    public static void main(String[] args) throws Exception {
        String url = "jdbc:sqlite:StudentSQLite_Practice.db";

        String sql = "CREATE TABLE test(test1 INT);";

        try {
            Connection con = DriverManager.getConnection(url);
            PreparedStatement pst = con.prepareStatement(sql);
            pst.executeUpdate();
            System.out.println("Success!");
        } catch (SQLException e) {
            System.out.println(e);
        }
    }
}
