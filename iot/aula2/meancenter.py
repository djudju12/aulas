import numpy as np
import matplotlib.pyplot as plt

def main():
    data = np.loadtxt("data.txt", delimiter='\t')
    meancenter = data - data.mean()   
    autoescalar = meancenter / data.std()
    plt.subplot(1,3,1)
    # plt.imshow(data)
    plt.plot(data.flatten())
    
    plt.subplot(1,3,2)
    # plt.imshow(meancenter)
    plt.plot(meancenter.flatten())

    plt.subplot(1,3,3)
    plt.plot(autoescalar.flatten())

    # plt.imshow(autoescalar)
    plt.show()


if __name__ == '__main__':
    main()