import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JFormattedTextField;
import javax.swing.JButton;
import javax.swing.JComboBox;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.text.DecimalFormat;
import java.util.HashMap;

public class ConverterApp extends JFrame implements ActionListener {
    // GUI components
    private JPanel panel1;
    private JPanel panel2;
    private JComboBox<String> currency1Box;
    private JComboBox<String> currency2Box;
    private JFormattedTextField amount1;
    private JFormattedTextField amount2;
    private JLabel convertFrom;
    private JLabel convertTo;
    private DecimalFormat amountFormat = new DecimalFormat(",###.##");
    private JButton convertButton;

    // GUI data
    private Dimension appSize = new Dimension(700, 160);
    private Dimension amountSize = new Dimension(200,25);
    private Font mainFont = new Font("sans-serif",Font.PLAIN,18);

    // App data
    private String[] currenciesList;
    private HashMap<String,String> currenciesMap;

    // Constructor; builds GUI
    ConverterApp () {
        // App frame settings
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Currency Converter");
        this.setSize(appSize);
        this.setResizable(false);
        this.setLayout(new FlowLayout(FlowLayout.RIGHT));
        this.setLocationRelativeTo(null);
        this.getContentPane().setBackground(Color.darkGray);

        // Input panels
        panel1 = new JPanel();
        panel2 = new JPanel();
        panel1.setOpaque(false);
        panel2.setOpaque(false);

        // Currency selectors
        currenciesMap = CurrencyApi.getCurrencies();
        currenciesList = currenciesMap.keySet().toArray(new String[currenciesMap.size()]);

        currency1Box = new JComboBox<String>(currenciesList);
        currency1Box.setSelectedItem("United States Dollar");
        currency2Box = new JComboBox<String>(currenciesList);

        // Labels
        convertFrom = new JLabel("Convert from:");
        convertTo = new JLabel("Convert to:");
        convertFrom.setFont(mainFont);
        convertTo.setFont(mainFont);
        convertFrom.setForeground(Color.white);
        convertTo.setForeground(Color.white);
        convertFrom.setLabelFor(currency1Box);
        convertTo.setLabelFor(currency2Box);

        // Money amounts
        amount1 = new JFormattedTextField(amountFormat);
        amount2 = new JFormattedTextField(amountFormat);

        amount1.setPreferredSize(amountSize);
        amount2.setPreferredSize(amountSize);
        amount1.setFont(mainFont);
        amount2.setFont(mainFont);

        amount2.setEditable(false);

        // Enter button
        convertButton = new JButton("Convert");
        convertButton.addActionListener(this);

        // Adds & set visibility
        panel1.add(convertFrom);
        panel1.add(currency1Box);
        panel1.add(amount1);
        panel2.add(convertTo);
        panel2.add(currency2Box);
        panel2.add(amount2);

        this.add(panel1);
        this.add(panel2);
        this.add(convertButton);
        this.setVisible(true);
    }

    // Action triggered on user click of "Convert" button; runs convertCurrencies and returns result
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == convertButton && amount1.getValue() != null) {
            String currency1 = currenciesMap.get((String)currency1Box.getSelectedItem());
            String currency2 = currenciesMap.get((String)currency2Box.getSelectedItem());

            double value = CurrencyApi.convertCurrencies(
                    currency1,
                    currency2,
                    Double.parseDouble(amount1.getValue().toString())
                );
            amount2.setValue(value);
        }
    }

}
