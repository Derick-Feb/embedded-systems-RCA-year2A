# 💳 RFID Dashboard - team_07

A modern and intuitive RFID card management system built with Node.js, Express, and WebSocket technology. This dashboard allows users to view their card balance in real-time and perform top-up transactions seamlessly with a high-end dark mode interface.

## 🌐 Live Site

Access the application here: **[http://localhost:9207](http://localhost:9207)**

## ✨ Features

- **Real-time Updates**: WebSocket-based live balance updates for instant feedback.
- **Card Detection**: Automatic RFID card detection and display with visual status indicators.
- **Top-up Functionality**: Easy balance top-up with instant confirmation and loading states.
- **MQTT Integration**: Connected to MQTT broker (`broker.benax.rw`) for card status updates.
- **Modern UI**: Premium Glassmorphism dark-mode design built with Tailwind CSS.
- **Responsive Design**: Works seamlessly on desktop and mobile devices.
- **Status Feedback**: Real-time success and error messages with color-coded alerts.

## 🛠️ Technology Stack

- **Backend**: Node.js with Express.js
- **Real-time Communication**: WebSocket (WS)
- **IoT Integration**: MQTT Protocol
- **Frontend**: HTML5, Tailwind CSS, Vanilla JavaScript
- **Port**: 9207

## 📋 Project Structure

card/
├── server.js           # Express server & WebSocket handler
├── index.html          # Modern Dark-Mode Dashboard UI
├── card.ino            # Arduino RFID card reader code
├── package.json        # Dependencies and scripts
└── README.md           # This file

```

## 🚀 Getting Started

### Prerequisites

- Node.js (v14 or higher)
- npm

### Installation

```bash
# Install dependencies
npm install express ws mqtt cors

# Start the server
node server.js

```

The server will start on `http://localhost:9207`

## 📡 How It Works

1. **Card Detection**: The Arduino-based RFID reader detects card UIDs and publishes them to the MQTT broker at `rfid/team_07/card/status`.
2. **WebSocket Connection**: The client connects via WebSocket to port 9207 to receive real-time balance updates.
3. **Balance Management**: Balances are stored on the backend in-memory and synchronized across all connected clients.
4. **Top-up API**: POST requests to the `/topup` endpoint update card balances and broadcast the change instantly.

## 🔌 API Endpoints

### POST `/topup`

Add funds to a card

**Request Body:**

```
{
  "uid": "card_uid_here",
  "amount": 100
}

```

**Response:**

```
{
  "success": true,
  "uid": "card_uid_here",
  "balance": 150
}

```

## 🔗 WebSocket Events

* **Connection**: Establishes real-time communication with the server (9207).
* **Message**: Receives card UID and balance updates.

```
{
  "uid": "card_uid_here",
  "balance": 150
}

```

## 🎨 UI Design

* **Color Scheme**: Modern Slate and Indigo Dark Mode.
* **Styling**: Glassmorphism effects with Tailwind CSS.
* **Responsive**: Optimized for mobile-first interactions.
* **Performance**: Lightweight assets with smooth CSS transitions.

## 📦 Dependencies

* `express`: Web server framework.
* `ws`: WebSocket library for real-time data.
* `mqtt`: Client for the IoT broker connection.
* `cors`: Cross-origin resource sharing support.

## 👥 Team

Developed by **team_07**

## 📝 License

ISC

```

Would you like me to provide the `card.ino` file mentioned in the project structure to complete the hardware part of the example?

```