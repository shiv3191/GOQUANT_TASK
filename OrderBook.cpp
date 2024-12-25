#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback function to handle the response from the HTTP request
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to get the order book
std::string get_orderbook(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the callback to handle the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the HTTP request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // If successful, you can parse or print the response
            std::cout << "Order Book Response: " << response << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize CURL" << std::endl;
    }

    // Clean up global libcurl resources
    curl_global_cleanup();
    return response;
}

int main() {
    // Example API endpoint for getting order book for BTC-PERPETUAL
    std::string url = "https://test.deribit.com/api/v2/public/get_orderbook?instrument_name=BTC-PERPETUAL";

    // Fetch the order book
    std::string result = get_orderbook(url);
    
    // Print the raw API response
    std::cout << "API Response: " << result << std::endl;

    return 0;
}
