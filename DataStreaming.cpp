#include <libwebsockets.h>  // Include libwebsockets library
#include <iostream>

int callback_websocket(struct lws *wsi, enum lws_callback_reasons reason,
                       void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_CLIENT_RECEIVE:
            // When data is received over the WebSocket
            std::cout << "Received data: " << std::string((char*)in, len) << std::endl;
            break;
        default:
            break;
    }
    return 0;
}

void start_websocket() {
    struct lws_context_creation_info info;
    struct lws_context *context;
    struct lws *websocket;

    // Initialize info structure for WebSocket context creation
    memset(&info, 0, sizeof(info));
    info.port = CONTEXT_PORT_NO_LISTEN;  // We don't need to listen to a port on this client
    info.protocols = (struct lws_protocols[]){  // Define supported protocols
        {"my-protocol", callback_websocket, 0, 0},  // Define protocol with a callback function
        {NULL, NULL, 0, 0}  // End of protocols
    };

    context = lws_create_context(&info);  // Create WebSocket context
    if (context == NULL) {
        std::cerr << "WebSocket context creation failed!" << std::endl;
        return;
    }

    // Connect to the WebSocket server
    websocket = lws_client_connect(context, "test.deribit.com", 443, 0, "/ws/api/v2", "", NULL, NULL, NULL);

    // Start processing WebSocket events (e.g., receiving messages)
    while (lws_service(context, 0) >= 0) {}

    lws_context_destroy(context);  // Clean up and destroy WebSocket context
}

int main() {
    start_websocket();  // Start WebSocket connection
    return 0;
}
