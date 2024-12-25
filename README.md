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


### Flow Chart

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




