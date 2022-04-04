#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point{
    int xCoordinate;
    int yCoordinate;
};

int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->xCoordinate - p2->xCoordinate);
}
     
    int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->yCoordinate - p2->yCoordinate);
}
    
class PointSpace{
    int numberOfPoints;
    vector<Point> points;

public:
    void setNumberOfPoints(int n){
        numberOfPoints = n;
    }
    
    int getNumberOfPoints(){
        return numberOfPoints;
    }
    
    void addPoint(int x, int y){
        Point p = Point();
        p.xCoordinate = x;
        p.yCoordinate = y;
        
        points.push_back(p);
    }
    
    
    void printNumberOfPoints(){
        cout << "Total number of points: " << getNumberOfPoints() << endl;
    }
    
    void printAllPoints(){
        cout << "Points coordinates (x y): " << endl;
        
        for (std::vector<Point>::const_iterator i = points.begin(); i != points.end(); ++i){
            cout << i->xCoordinate << "\t" << i->yCoordinate << endl;
        }
    }
    
   
    double FindClosestPairDistance(){
        // FILL HERE
        Point P[numberOfPoints];
        for(int i=0; i<numberOfPoints; i++){
            P[i] = points[i];
        }
        qsort(P, numberOfPoints, sizeof(Point), compareX);
        return closestRec(P,numberOfPoints);
        // You may define new functions if you need
    }
       
    double stripClosest(Point strip[], int size, double dis)
    {
        double min = dis;
     
        qsort(strip, size, sizeof(Point), compareY);
     
        for (int i = 0; i < size; ++i)
            for (int j = i+1; j < size && (strip[j].yCoordinate - strip[i].yCoordinate) < min; ++j)
                if (dist(strip[i],strip[j]) < min)
                    min = dist(strip[i], strip[j]);
     
        return min;
    }
    
    double closestRec(Point P[], int num){
        if(num<=3){
            double min = 999999;
            for (int i = 0; i < numberOfPoints; ++i){
                for (int j = i+1; j < numberOfPoints; ++j){
                    if (dist(points[i], points[j]) < min){
                        min = dist(points[i], points[j]);
                    }
                }
            }
            return min;
        }
        
        double d =0;
        int mid = num/2;
        Point midPoint = P[mid];
     
        
        double left = closestRec(P, mid);
        double right = closestRec(P + mid, num - mid);
     
        // Find the smaller of two distances
        double d = min(left, right);
        
        Point strip[num];
        int x = 0;
        for (int i = 0; i < num; i++)
            if (abs(P[i].xCoordinate - midPoint.xCoordinate) < d)
                strip[x] = P[i], x++;
     
        return min(d, stripClosest(strip, x, d) );
            
    }
    
    double dist(Point p1, Point p2){
         return sqrt( (p1.xCoordinate - p2.xCoordinate)*(p1.xCoordinate - p2.xCoordinate) +
                (p1.yCoordinate - p2.yCoordinate)*(p1.yCoordinate - p2.yCoordinate)
            );
    }
};



int main(int argc, char* argv[]){
    //define a point space
    PointSpace pointSpace;

    //get file name
    string inputFileName;
    cin>>inputFileName;
    
    string line;
    ifstream infile(inputFileName);

    //read the number of total points (first line)
    getline(infile, line);
    pointSpace.setNumberOfPoints(stoi(line));

    //read points' coordinates and assign each point to the space (second to last line)
    int x, y;
    while (infile >> x >> y){
       pointSpace.addPoint(x, y);
    }
    
    //print details of point space (not necessary for assignment evaluation: calico will not check this part)
    pointSpace.printAllPoints();
    pointSpace.printNumberOfPoints();
    
    //find and print the distance between closest pair of points (calico will check this part)
    double closestDistance = pointSpace.FindClosestPairDistance();
    cout << "Distance between the closest points: " << closestDistance << endl;
    
    return 0;
}



