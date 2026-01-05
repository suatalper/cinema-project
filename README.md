# Cinema Reservation System

A console-based cinema booking system written in C. This application allows users to browse films and reserve seats, while employees can manage the film catalog and monitor seat occupancy.

## Features

### For Customers (Users)

- **Account Management**: Register specific user accounts and log in securely.
- **Browse Films**: View a list of currently showing movies and their ticket prices.
- **View Seating**: Check the real-time availability of seats in the salon (5 rows x 10 columns).
- **Make Reservations**: Book specific seats (e.g., Row A, Seat 5).
- **My Reservations**: View your personal reservation history.

### For Employees (Admins)

- **Film Management**: Add new movies to the listings or remove existing ones.
- **Monitor Halls**: View the seating status for any specific film.
- **Employee Access**: Secure login for authorized personnel.

## technical Details

- **Language**: C
- **Data Persistence**: Uses simple text files (`.txt`) to store all data (users, films, reservations, seat layouts).
- **Seat Layout**: Fixed 5x10 grid (Rows A-E, Columns 1-10).
- **Platform**: Windows (Dependencies: `<windows.h>` for character encoding).

## File Structure

- `cinema.c`: The main source code.
- `customers.txt`: Stores user credentials.
- `employees.txt`: Stores employee credentials.
- `films.txt`: Stores the list of active films and prices.
- `reservations.txt`: Stores reservation records.
- `[FilmName]_salon.txt`: Auto-generated files storing the seat matrix for each film.

## compilation & Setup

### Prerequisites

- A C compiler (GCC recommended, e.g., MinGW).
- Windows Operating System.

### How to Compile

Open your terminal in the project directory and run:

```bash
gcc cinema.c -o cinema.exe
```

### How to Run

```bash
./cinema.exe
```

## Usage Notes

- **Interface Language**: The application interface is in **Turkish**.
- **Input Format**: When entering film names, use underscores instead of spaces (e.g., `Spider_Man` instead of `Spider Man`).
