# C++ Inventory Management System

A full-stack Web Application built using Object-Oriented Principles (OOP) in C++. This project demonstrates how robust C++ backend logic can power a lightweight, modern web interface.

## 🌟 Features

- **C++ REST API Backend**: Built entirely in C++ using the lightweight `cpp-httplib` microframework.
- **Modern Web Interface**: A sleek, dynamic single-page web application using standard HTML/CSS/JS with a glassmorphism aesthetic.
- **Persistent Storage**: Data is seamlessly written and loaded from a local `inventory_data.csv` file, ensuring no data loss across server restarts.
- **Full CRUD Operations**: Users can Create, Read, Update, and Delete inventory items tracking IDs, Names, Quantities, and Pricing.
- **Docker Ready**: Includes a fully configured `Dockerfile` ready for easy containerization and deployment onto cloud platforms.

## 🛠️ Tech Stack

- **Backend Logic & Routing**: C++11 standard, utilizing standard libraries, object properties, and standard template collections (Vectors).
- **Web Microframework**: `cpp-httplib`
- **JSON Serialization**: `nlohmann/json` 
- **Frontend**: Vanilla HTML5, CSS3, and JavaScript
- **Build System**: `make` / `g++` and Docker

## 🚀 Getting Started Locally

You have two primary ways of running this application on your local machine: using Docker (Recommended) or Compiling Manually.

### Method 1: Using Docker (Requires Docker Desktop)

Running the application through Docker ensures you do not need to worry about compilers and libraries installed on your machine.

1. Ensure the Docker daemon is running.
2. Build the Docker Image:
   ```bash
   docker build -t inventory-system .
   ```
3. Run the Container on port 8080:
   ```bash
   docker run -p 8080:8080 inventory-system
   ```
4. Access the web interface in your browser at `http://localhost:8080`.

### Method 2: Manual Compilation (Linux)

If you prefer building native binaries locally, ensure you have `-pthread` and compiling capabilities installed (`build-essential`).

1. Clean previous build artifacts and run the compiler via Make:
   ```bash
   make clean && make
   ```
2. Run the newly generated binary server:
   ```bash
   ./inventory_system
   ```
3. Access the web interface in your browser at `http://localhost:8080`.

## ☁️ Cloud Deployment

This project contains a Dockerfile perfectly tailored for cloud deployment platforms that support containerized environments (such as Render, Railway, or Fly.io).

Example deployment workflow on Render:
1. Push this repository to GitHub.
2. Connect the repository to Render as a "Web Service".
3. Render automatically reads the `Dockerfile`, handles compiling your C++ codebase, exposes the 8080 port natively, and provisions a public web URL.
