#include <iostream>
#include <vector>
using namespace std;
typedef struct {
    // The ID of The Polygon
    int id;
    // The X, Y value of The Button Left side
    int bottom_left_x;
    int bottom_left_y;
    // The X, Y value of The Top Right side
    int top_right_x;
    int top_right_y;
    int net_id;
    int layer_id;
    int type;
}Polygon;


Polygon findEmptyRectangle(vector <vector <bool> > &window_map, vector<int> &clX, vector<int> &clY, int currentLayer){
    //Declare Dynamic programming variable.
    Polygon emptyRectangle;
    vector<int> wl(window_map[0].size(), 0);
    vector<int> wr(window_map[0].size(), 0);
    vector<int> h(window_map[0].size(), 0);
    vector<int> l(window_map[0].size(), 0);
    vector<int> r(window_map[0].size(), 0);

    vector<int> wl_pos(window_map[0].size(), 0);
    vector<int> wr_pos(window_map[0].size(), 0);
    vector<int> h_pos(window_map[0].size(), 0);
    vector<int> l_pos(window_map[0].size(), 0);
    vector<int> r_pos(window_map[0].size(), 0);
    int max_area = 0;

    //Dynamic Programming Algorithm
    for (int j = 0; j < window_map.size(); ++j)
    {

        for (int i = 0; i < window_map[j].size(); ++i){
            if (window_map[j][i]){
                wl[i] = (i > 0)? wl[i - 1] + (clX[i+1]-clX[i]) : clX[1]-clX[0];
                wl_pos[i]= (i > 0)? wl_pos[i - 1] + 1 : 1;
            }
            else{
                wl[i] = 0;
                wl_pos[i]=0;
            }
        }


        for (int i=window_map[j].size()-1; i>=0; --i)
        {
            if (window_map[j][i])
            {
                wr[i] = (i < window_map[j].size()-1)? wr[i+1] + (clX[i]-clX[i-1]) :  clX[window_map[j].size()]-clX[window_map[j].size()-1];
                wr_pos[i] = (i < window_map[j].size()-1)? wr_pos[i+1] + 1 :  1;
            }
            else
            {
                wr[i] = 0;
                wr_pos[i]=0;
            }
        }


        for (int i = 0; i < window_map[j].size(); ++i)
        {
            if (window_map[j][i])
            {
                h[i] = h[i] + (clY[j+1]-clY[j]);
                h_pos[i] = h_pos[i] + 1;
            }
            else
            {
                h[i] = 0;
                h_pos[i] = 0;
            }
        }


        for (int i = 0; i < window_map[j].size(); ++i)
        {
            if (l[i] == 0)
            {
                l[i] = wl[i];
                l_pos[i] = wl_pos[i];
            }
            else
            {
                if(l[i] < wl[i])
                {
                    //l[i] is min
                }
                else
                {
                    //wl[i] is min
                    l[i] = wl[i];
                    l_pos[i] = wl_pos[i];
                }

            }

        }


        for (int i = 0; i < window_map[j].size(); ++i)
        {
            if (r[i] == 0)
            {
                r[i] = wr[i];
                r_pos[i] = wr_pos[i];
            }
            else
            {
                if(r[i] < wr[i])
                {
                    //r[i] is min
                }
                else
                {
                    //wr[i] is min
                    r[i] = wr[i];
                    r_pos[i] = wr_pos[i];
                }
            }
        }


        for (int i = 0; i < window_map[j].size(); ++i){
            int width = l[i] + r[i] - (clX[i+1]-clX[i]);
            int height = h[i];
            int condition = 65 + 65;
            if(width >= condition)
            {
                if(height >= condition)
                {
                    if(max_area <= (l[i] + r[i] - (clX[i+1]-clX[i])) * h[i]){
                        //cout << "Max Parameter:" << l[i] << " " << r[i] << " " << h[i] << " " << window_map.size() << " " << window_map[j].size() << endl;
                        emptyRectangle.bottom_left_x = i - (l_pos[i] - 1);
                        emptyRectangle.bottom_left_y = j - (h_pos[i] - 1);
                        emptyRectangle.top_right_x = i + (r_pos[i] - 1);
                        emptyRectangle.top_right_y = j;
                        max_area = (l[i] + r[i] - (clX[i+1]-clX[i])) * h[i];
                        cout << i << " " << j << " " << width << " " << height << "\n";
                        cout << l_pos[i] << " " << h_pos[i] << " " << r_pos[i] << endl;
                    }
                }

            }

            //max_area = max(max_area, (l[j] + r[j] - 1) * h[j]);
        }

    }
    //cout << "Max area: " << max_area << endl;
    //cout<<"("<<emptyRectangle.bottom_left_x<<", "<<emptyRectangle.bottom_left_y<<"), ("<<emptyRectangle.top_right_x<<", "<<emptyRectangle.top_right_y<<")\n";
    //system("pause");
    //return max_area;
    return emptyRectangle;
}


int main()
{
    vector<int> clX={65, 129, 210, 245 ,300, 340, 390};
    vector<int> clY={53, 130, 145, 200, 1240, 1490};
    vector< vector<bool> > window_map;
    for(int i =0; i<5; i++){
        vector<bool>new_row;
        for(int j=0;j<6;j++){
            new_row.push_back(true);
        }
        window_map.push_back(new_row);
    }

    window_map[2][1]=false;
    window_map[3][4]=false;
    window_map[0][2]=false;
    window_map[4][5]=false;
    window_map[2][5]=false;
    window_map[1][3]=false;
    for(int y=window_map.size()-1; y>=0; y--){
        for(int x=0; x<window_map[0].size(); x++){
            if(window_map[y][x]==true)cout<<"- ";
            else cout<<"+ ";
        }
        cout<<"\n";
    }
    Polygon IndexofEmptyRegtangle = findEmptyRectangle(window_map, clX, clY, 0);
    Polygon emptyRectangle;
    emptyRectangle.bottom_left_x = clX[IndexofEmptyRegtangle.bottom_left_x];
    emptyRectangle.bottom_left_y = clY[IndexofEmptyRegtangle.bottom_left_y];
    emptyRectangle.top_right_x = clX[IndexofEmptyRegtangle.top_right_x+1];
    emptyRectangle.top_right_y = clY[IndexofEmptyRegtangle.top_right_y+1];
    cout<<"Index: "<<IndexofEmptyRegtangle.bottom_left_x<<" "<<IndexofEmptyRegtangle.bottom_left_y<<" "<<IndexofEmptyRegtangle.top_right_x<<" "<<IndexofEmptyRegtangle.top_right_y<<"\n";
    cout<< emptyRectangle.bottom_left_x << " " << emptyRectangle.bottom_left_y << " " << emptyRectangle.top_right_x << " " << emptyRectangle.top_right_y << endl;

    return 0;
}
