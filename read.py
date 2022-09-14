import serial

import argparse
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

import pytz
from datetime import datetime

class DataReader():
    def __init__(self, port, baud_rate, title, ylabel, interval):
        self.ser = serial.Serial(port, baud_rate)
        print('Connect!')

        self.graph_title = title
        self.graph_ylabel = ylabel
        self.interval = interval

    def draw(self):
        xs = []
        ys = []
        fig = plt.figure()
        self.ax = fig.add_subplot(1, 1, 1)

        ani = FuncAnimation(fig, self.animate, fargs=(xs, ys), interval=self.interval)
        plt.show()
        
    def animate(self, i, xs, ys):
        if self.ser.in_waiting:

            # get data
            data_raw = self.ser.readline()
            data = data_raw.decode()[:-1]

            # get time 
            tz_TW = pytz.timezone('Asia/Taipei') 
            datetime_TW = datetime.now(tz_TW)
            xs.append(datetime_TW)
            ys.append(float(data))

            # plot the last 20 data
            xs = xs[-20:]
            ys = ys[-20:]

            self.ax.clear()
            self.ax.plot(xs, ys)
            # ax.set(ylim=(0, 10))

            # Format plot, you can change labels and titles for different usage
            plt.xticks(rotation=45, ha='right')
            plt.subplots_adjust(bottom=0.30)
            plt.title(self.graph_title)
            plt.ylabel(self.graph_ylabel)

if __name__ == "__main__":

    # config
    # You can find your device (e.g. arduino board) in "/dev" directory for linux system
    # Baud rate must be the same as the one in arduino Serial setup.

    parser = argparse.ArgumentParser()
    parser.add_argument("-t", "--title", help="Please enter the title of the graph.", default="", type=str)
    parser.add_argument("-y", "--ylabel", help="Please enter the y label of the graph.", default="", type=str)
    parser.add_argument("-b", "--baudrate", help="Please enter the baud rate of the UART connection.", default=9600, type=int)
    parser.add_argument("-i", "--interval", help="Please enter how many frames you want to read for graph plotting.", default=10000, type=int)

    required = parser.add_argument_group('Required named arguments')
    required.add_argument("-p", "--port", help="Please enter the port of the UART connection.", required=True, type=str)

    args = parser.parse_args()

    # read and plot data
    reader = DataReader(port=args.port, baud_rate=args.baudrate, title=args.title, ylabel=args.ylabel, interval=args.interval)