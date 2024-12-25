#include <iostream>
#include <string>
#include <curl/curl.h>  // For handling HTTP requests

// Callback function to store the HTTP response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);  // Append data to the response string
    return size * nmemb;  // Return the number of bytes written
}

// Function to cancel an order by making a POST request
std::string cancel_order(const std::string& url, const std::string& params) {
    CURL* curl;          // CURL handle for HTTP requests
    CURLcode res;        // Result code for error checking
    std::string response;  // To store the server's response

    // Initialize CURL globally
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();  // Initialize a CURL session

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  // Set the API URL
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());  // Set the POST data

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  // Handle the server's response
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);  // Store the response in the string

        res = curl_easy_perform(curl);  // Execute the HTTP POST request

        if (res != CURLE_OK) {  // Check for request errors
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);  // Clean up the CURL session
    }

    curl_global_cleanup();  // Clean up global CURL resources
    return response;  // Return the server's response
}

int main() {
    // Example API endpoint and parameters
    std::string url = "https://test.deribit.com/api/v2/private/cancel_order";  // Cancel order API endpoint
    std::string params = "order_id=123456";  // Replace with the actual order ID to cancel

    // Call the function to cancel the order and print the result
    std::string result = cancel_order(url, params);
    std::cout << "API Response: " << result << std::endl;

    return 0;
}
