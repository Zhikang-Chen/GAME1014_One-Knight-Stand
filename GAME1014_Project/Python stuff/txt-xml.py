#If I can marry a programming language I will choose python because it allow me to be lazy.
#Also I can have array of mix type. TAKE THAT vector.
import xml.etree.ElementTree as ET
TXTFILE = "Tiledata.txt"
XMLFILE = "TileData.xml"

def readtxt(FileName):
    infile = open(FileName, "r")
    List = []
    s = infile.readline()
    while s != "":
        #print(s.strip())
        List.append(s)
        s = infile.readline()
    infile.close()
    return List;


def main():
    print("fuck my life 0.1")
    arr = []

    for i in readtxt(TXTFILE):
        s = ""
        a = []
        #print(i)
        for c in i:
            if c == " ":
                a.append(s);
                s = ""
            else:
                s += c
        arr.append(a)
        #print(a)

    data = ET.Element('Data')
    data.text = "\n"
    for a in arr:
        if len(a) == 5:
            tile = ET.SubElement(data, "Tile")
            tile.set("key",a[0])
            tile.set("x",a[1])
            tile.set("y",a[2])
            tile.tail = "\n"
    tree = ET.ElementTree(data)
    tree.write(XMLFILE)


    

main()
