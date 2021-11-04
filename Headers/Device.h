#ifndef DEVICE_H_INCLUDED
#define DEVICE_H_INCLUDED

#define string std::string
#define cin std::cin

class Device{
protected:
    string type, mark;
    int year;
    double maxVal;
public:
    Device(){}
    Device(string _type, string _mark, double _maxVal, int _year):
        type(_type),
        mark(_mark),
        year(_year),
        maxVal(_maxVal)
        {}
    string getMark(){return mark;}
    double getMaxVal(){return maxVal;}
    int getYear(){return year;}
    bool operator<(Device a){
        if (mark == a.getMark()){
            if (year == a.getYear()){
                return (maxVal < a.getMaxVal());
            }else return (year < a.getYear());
        } else return (mark < a.getMark());
    }
    friend std::ostream &operator<<(std::ostream &, const Device);
};

std::ostream &operator<<(std::ostream &output, const Device a){
    output << a.type << ' ' << a.mark << ' ' << a.year << ' ' << a.maxVal;
    return output;
}

#endif // DEVICE_H_INCLUDED
