# Visualizing Data

This project utilizes Python to visualize the data collected by our benchmarking tools. It uses libraries such as Matplotlib and Seaborn to generate interactive plots
for use in demonstrating the latency improvements on Interpolation Search.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

You need to have Python installed on your machine. You can download Python [here](https://www.python.org/downloads/). This program also requires the following Python libraries:

- Matplotlib
- Seaborn

You can install these packages using pip:

```bash
pip install matplotlib seaborn
```
Additionally, this program requires a C++ compiler (g++) and the make utility.  If you're using a Debian-based Linux distribution, you can install these with the following command:


```sudo apt-get install g++ make```


### Running the Program

To run the benchmarks, you can run the Jupyter notebook within vscode or using a local server. The program will automatically compile all the outlined benchmarks
then plot them one at a time.