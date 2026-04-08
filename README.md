# Efficient One-Pass Private Set Intersection from Pairings with Offline Preprocessing
This project implements the protocols desribed in [Efficient One-Pass Private Set Intersection from Pairings with Offline Preprocessing](https://link.springer.com/chapter/10.1007/978-3-032-07891-9_3).

## Required Libraries

```bash
sudo apt install build-essential cmake git libssl-dev libgmp-dev
```

## Build the Project

```bash
mkdir build
cd build
cmake ..
make
```

## Running the Code
- `-p`: Port number
- `-n`: Sender's dataset log size
- `-m`: Receiver's dataset log size

## Example
``` bash
./bin/Semi_Honest_sender -p 1234 -n 8 -m 8
./bin/Semi_Honest_receiver -p 1234 -n 8 -m 8
```
