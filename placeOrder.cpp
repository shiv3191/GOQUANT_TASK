#include <iostream>
#include <curl/curl.h>  // For HTTP request handling

// Callback function to process HTTP response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);  // Append received data to response string
    return size * nmemb;
}

// Function to send an order placement request
std::string place_order(const std::string& url, const std::string& params) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);  // Initialize global CURL state
    curl = curl_easy_init();  // Start a CURL session

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  // Set API endpoint URL
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());  // Set POST parameters
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  // Handle server response
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);  // Store server response

        res = curl_easy_perform(curl);  // Execute HTTP POST request

        if (res != CURLE_OK) {  // Check for any request errors
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);  // Clean up the CURL session
    }

    curl_global_cleanup();  // Clean up global CURL resources
    return response;  // Return the API response
}

int main() {
    // Deribit API endpoint and order parameters
    std::string url = "https://test.deribit.com/api/v2/private/submit_order";
    std::string params = "instrument_name=BTC-PERPETUAL&price=50000&quantity=1&type=limit";

    // Place the order and print the API response
    std::string result = place_order(url, params);
    std::cout << "API Response: " << result << std::endl;

    return 0;
}
