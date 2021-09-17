## Overview

Application allows user to input a cash value and select its currency, then select a currency to convert it to and see the result.

## Purpose

Application created to practice Java, OOP, and GUI programming.

## Files Overview

Main.java is used to trigger the application.

ConverterApp.java builds the GUI and triggers events upon user input.

CurrencyApi.java performs the actual conversions; it interacts with an API to GET and manipulate relevant data (i.e. a list of all currencies, to be made available for user selection, and the conversion ratio between any two currencies).

Utils.java stores generic helper method. At this time, that is restricted to an HTTPS GET method.

## Dependencies

Application uses json-simple-1.1 in order to parse JSON output from the API.

Additionally, the API key used for connection is accessed from /lib/apiKey.txt for convenience (removed from GitHub upload for security).
