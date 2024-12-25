#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback function to handle the response from the HTTP request
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to modify an order
std::string modify_order(const std::string& url, const std::string& params) {
    CURL* curl;
    CURLcode res;
    std::string response;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        // Set POST fields
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());

        // Set callback to handle the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the HTTP request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Order modification response: " << response << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }
    // Clean up global libcurl resources
    curl_global_cleanup();
    return response;
}

int main() {
    // Example API endpoint and parameters
    std::string url = "https://test.deribit.com/api/v2/private/modify_order";
    std::string params = "order_id=123456&new_price=51000&new_quantity=2";  // Example order modification

    // Call the modify_order function and print the result
    std::string result = modify_order(url, params);
    std::cout << "API Response: " << result << std::endl;

    return 0;
}
