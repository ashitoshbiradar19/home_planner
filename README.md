# home_planner
# 🏠 Home Structure Planner

A C++ based home planning tool that helps you design,
calculate, and optimize your home layout before construction.

---

## 📌 Features

- Owner info & plot location input
- 4 predefined templates (1BHK, 2BHK, 3BHK, Villa)
- Custom room builder
- Edit / Delete rooms anytime
- Visual progress bar for space usage
- Construction cost estimator (Rs. Budget & Premium)
- Vastu Shastra tips
- Room type summary (Beds, Baths, Halls)
- Save report to .txt file
- Full input validation

---

## How to Run

### Step 1 - Compile
```bash
g++ home_planner.cpp
```

### Step 2 - Run
```bash
./a.out
```

---

##  Home Templates Available

| Template | Rooms Included |
|----------|----------------|
| 1 BHK    | Bedroom + Hall + Kitchen + Bathroom |
| 2 BHK    | 2 Beds + Hall + Kitchen + 2 Bathrooms |
| 3 BHK    | 3 Beds + Hall + Kitchen + 3 Baths + Balcony |
| Villa    | 4 Beds + 2 Halls + Kitchen + 4 Baths + Balcony + Garage |
| Custom   | Define your own rooms |

---

##  What It Calculates

- Total plot area & usable area (90% after wall deduction)
- Per room area and % of total plot
- Space utilization with progress bar
- Remaining area with suggestions
- Construction cost in Rs. (Budget & Premium range)

---

## 💰 Cost Estimate Rates

| Type    | Rate per sq ft |
|---------|----------------|
| Budget  | Rs. 1,200      |
| Premium | Rs. 2,000      |

> Excludes land cost, interior, and finishing charges.

---

## 🧭 Vastu Tips Included

- Main entrance direction
- Kitchen placement (South-East)
- Master Bedroom (South-West)
- Pooja Room (North-East)
- Bathroom placement guide

---

## 📁 Project Structure
```
sturdy_potato/
│
├── home_planner.cpp          # Main source code
├── a.out                     # Compiled output (auto generated)
├── home_report_<name>.txt    # Auto generated report after save
└── README.md                 # This file
```

---

## 🛠 Requirements

- Linux / Mac terminal
- g++ compiler (C++11 or higher)

### Install g++ if not installed
```bash
sudo apt install g++
```

---

## 👨‍💻 Author

**Ashitosh Biradar**
- GitHub: [@ashitoshbiradar19](https://github.com/ashitoshbiradar19)
