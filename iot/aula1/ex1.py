
def avarage():
    vet = []
    vet2 = []
    with open("data.txt", "r") as f:
        lines = f.readlines()
        print(len(lines))
        for line in lines:
            l = line.split("\t")
            for i, num in enumerate(l):
                try:
                    vet[i] += float(num)
                except IndexError:
                    vet.append(float(num))
        
        for item in vet:
            vet2.append(item/len(lines))

    with open("avarage.txt", "w") as w:
        w.write(str(vet2))

    return vet2

def mean_center():
    vet = []
    avgs = avarage()
    with open("data.txt", "r") as f:
        lines = f.readlines()
        for line in lines:
            l = line.split("\t")
            for i, num in enumerate(l):
                vet.append(float(num) - avgs[i])

    with open("meancenter.txt", "w") as w:
        w.write(str(vet))

def main():
    mean_center()
    return 

if __name__ == '__main__':
    main()