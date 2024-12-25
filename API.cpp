#include <iostream>
#include <curl/curl.h>  // For HTTP requests
#include <json/json.h>  // For parsing JSON

// Deribit API Base URL and credentials
const std::string BASE_URL = "https://test.deribit.com";
std::string client_id = "k1yYryQI";
std::string client_secret = "IspiDSwNfMqd0igwEi_cMWQQkwcD3plXicc6lq2gw64";
std::string access_token;

// Perform HTTP POST request and return the response
std::string httpRequest(const std::string& url, const std::string& params) {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, (BASE_URL + url).c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* data, size_t size, size_t nmemb, std::string* buffer) {
            buffer->append((char*)data, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

// Authenticate and get access token
void authenticate() {
    std::string url = "/api/v2/public/auth";
    std::string params = "client_id=" + client_id + "&client_secret=" + client_secret + "&grant_type=client_credentials";
    std::string response = httpRequest(url, params);

    Json::Value jsonResponse;
    Json::Reader reader;
    if (reader.parse(response, jsonResponse)) {
        if (!jsonResponse["result"].isNull() && jsonResponse["result"].isMember("access_token")) {
            access_token = jsonResponse["result"]["access_token"].asString();
            std::cout << "Access Token: " << access_token << std::endl;
        } else {
            std::cerr << "Error: Access token not found." << std::endl;
        }
    } else {
        std::cerr << "Error parsing JSON response." << std::endl;
    }
}

int main() {
    authenticate();
    return 0;
}
