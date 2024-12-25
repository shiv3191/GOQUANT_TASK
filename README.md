# Deribit Order Execution and Management System (C++)

This is a high-performance order execution and management system built to trade on Deribit Test (https://test.deribit.com/) using C++. It supports various functionalities like placing orders, canceling orders, modifying orders, viewing order books, real-time market data streaming via WebSocket, and more. The system is optimized for low-latency performance and robust error handling.

## Core Features

### Order Management
- **Place Order**: Submit buy/sell orders for instruments (Spot, Futures, Options).
- **Cancel Order**: Cancel existing orders based on order ID.
- **Modify Order**: Update order price or quantity.
- **Get Orderbook**: Fetch order book for specified instruments.
- **View Current Positions**: Retrieve current open positions.

### Real-Time Market Data (WebSocket)
- Implement WebSocket server functionality for real-time streaming of order book data.
- Clients can subscribe to specific symbols to receive continuous updates.

### Market Coverage
- **Instruments**: Spot, Futures, Options
- **Scope**: All supported symbols

## Installation

### Prerequisites
1. **C++ compiler** (C++14 or later)
2. **libcurl** for HTTP requests
3. **websocketpp** for WebSocket communication
4. **jsoncpp** for JSON parsing
5. **Boost** libraries

## Latency Benchmarking

### Key Metrics:
1. **Order Placement Latency**: Measures the time taken to send an order and receive acknowledgment from the Deribit API.
2. **Market Data Processing Latency**: Time to process the market data after it is received.
3. **WebSocket Message Propagation Delay**: Measures the delay between sending and receiving a WebSocket message.
4. **End-to-End Trading Loop Latency**: The total time taken from receiving market data to placing an order and confirming the execution.

---

## Optimization Techniques

### Areas of Focus:
1. **Memory Management**: Optimized memory allocation and deallocation to reduce overhead.
2. **Network Communication**: Minimized unnecessary network requests to optimize communication.
3. **Data Structure Selection**: Utilized efficient data structures (e.g., hash maps, arrays) for fast data processing.
4. **Thread Management**: Implemented basic multi-threading for concurrent order execution and market data processing.
5. **CPU Optimization**: Applied basic CPU optimization to reduce processing time for intensive tasks.

---

## Performance Metrics

1. **Before Optimization**: Performance metrics are captured to assess the initial latency and resource consumption.
2. **After Optimization**: Performance improvements have been made in network and memory usage for faster order execution.

---
   
# Order Execution and Management System Flow

The following flowchart illustrates the process of executing and managing orders on the Deribit Test platform:

```plaintext
Start  
  |  
  v  
Initialize Connection to Deribit API  
  |  
  v  
User Inputs Order Details  
  |  
  v  
Validate Inputs -------------------> [Error] ---> End  
  |  
  v  
Create Order  
  |  
  v  
Send Order to Deribit API  
  |  
  v  
Wait for Response  
  |  
  v  
Order Rejected --------------------> [Error] ---> End  
  |  
  v  
Order Confirmation  
  |  
  v  
Track Order Status  
  |   
  v  
[Order Filled] ---> Process Order ---> End  
  |  
  v  
[Order Open] ---> Wait or Cancel Order  
  |  
  v  
End
