
# 🛰️ RFID Nexus | Team_07 Dashboard

> A premium, real-time RFID management ecosystem powered by Node.js and IoT protocols.

---

## 🦾 Overview

The **RFID Dashboard** is a high-end card management system designed for instant synchronization. Utilizing a glassmorphism dark-mode interface, it provides users with immediate visibility into their card status and financial balance via persistent WebSocket connections.

### ⚡ Key Features

* **📡 Live Sync**: Instant balance updates via WebSockets.
* **💸 Seamless Top-ups**: Rapid fund injection with built-in loading states.
* **☁️ IoT Ready**: Fully integrated with the `broker.benax.rw` MQTT broker.
* **💎 Glassmorphism UI**: A sleek, responsive design crafted with Tailwind CSS.

---

## ⚙️ Tech Stack & Architecture

| Layer | Technology | Purpose |
| --- | --- | --- |
| **🎨 Frontend** | HTML5, Tailwind CSS, JS | Modern Responsive UI |
| **🖥️ Backend** | Express.js | API & Static file hosting |
| **🔌 Real-time** | WebSocket (WS) | Bidirectional live updates |
| **📟 IoT Connectivity** | MQTT Protocol | RFID Reader communication |
| **🛠️ Hardware** | Arduino (ESP8266/ESP32) | Physical card scanning |

### 📂 Project Structure

```text
card/
├── server.js          # Logic: Express & WebSocket Handler
├── index.html         # UI: Glassmorphism Dashboard
├── card.ino           # Hardware: RFID Reader Firmware
├── package.json       # Metadata & Dependencies
└── README.md          # Project Documentation

```

---

## 🚀 Getting Started

### 1. Prerequisites

* **Node.js**: v14.0.0+
* **NPM**: v6.0.0+

### 2. Quick Start

```bash
# Clone and enter the directory
cd card

# Install dependencies
npm install express ws mqtt cors

# Launch the dashboard
node server.js

```

🔗 **Access the UI:** [http://localhost:9207](https://www.google.com/search?q=http://localhost:9207)

---

## 🧠 System Logic

The system operates on a four-stage communication loop:

1. **Detection**: Arduino scans a card and publishes the UID to `rfid/team_07/card/status`.
2. **Broker**: The MQTT broker relays the message to the Node.js server.
3. **WebSocket**: The server pushes the new balance/UID to all connected browser clients.
4. **Interaction**: Users perform top-ups via the UI, which triggers a POST request to update the state.

---

## 🛠️ API & Events

### 🌐 REST API

**`POST /topup`** Used to add funds to a specific card.

* **Payload:**
```json
{ "uid": "A1B2C3D4", "amount": 100 }

```


* **Success Response:**
```json
{ "success": true, "uid": "A1B2C3D4", "balance": 150 }

```



### 🤝 WebSocket Message

Clients receive a JSON object whenever a card is scanned or updated:

```json
{
  "uid": "A1B2C3D4",
  "balance": 150
}

```

---

## 🧪 Development Team

Developed with by **Team_07**.