#include<iostream>
#include<fstream>
#include<vec3.h>
void test01()
{
    int nx = 200;
    int ny = 100;
    std::ofstream ofs("image.ppm",std::ios::out);
    ofs<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    for(int j=ny-1;j>=0;j--)
    {
        for(int i=0;i<nx;i++)
        {
            vec3 col(float(i)/float(nx),float(j)/float(ny),0.2);
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());
            ofs<<ir<<" "<<ig<<" "<<ib<<"\n";
        }
    }
}
int main()
{
    test01();
}