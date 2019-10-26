#include<bits/stdc++.h>
#include "time.h"
#include<fstream>
using namespace std;

  
  
double add_random_noise(double a, double delta){
    double noise = ((double)((rand() % int(2 * delta * 10000)))/ 10000 ) - delta;

    return a + noise;
}


vector< vector < pair < double, double> > > swarm(vector<pair<double, double> > position_vect, vector< pair< double, double > > destinations_vect, int time){
        vector<double> euclidian_distance_vect;
        vector<int> time_distribution_vect;
        
        euclidian_distance_vect.push_back(sqrt(pow(destinations_vect[0].first - position_vect[0].first, 2) + pow(destinations_vect[0].second - position_vect[0].second, 2)));
        for(int i = 0; i < destinations_vect.size() - 1; i++){
            euclidian_distance_vect.push_back(sqrt(pow(destinations_vect[i].first - destinations_vect[i + 1].first, 2) + pow(destinations_vect[i].second - destinations_vect[i + 1].second, 2)));
		}
        
        double distance_sum = 0;
        for(int i = 0 ; i < euclidian_distance_vect.size(); i++){
            distance_sum += euclidian_distance_vect[i];
        }

        for(int i = 0 ; i < euclidian_distance_vect.size(); i++){
            time_distribution_vect.push_back(1 + time * euclidian_distance_vect[i] / distance_sum);
        }

        double noise_for_deer = 0.0005;
		double noise_for_deer_small = 0.1;

        for(int i = 0 ; i < position_vect.size(); i++){
            position_vect[i].first = add_random_noise(position_vect[i].first, 10 * noise_for_deer);
            position_vect[i].second = add_random_noise(position_vect[i].second, 10 * noise_for_deer);
        }

        vector< vector < pair < double, double> > > output_vect;

        output_vect.push_back(position_vect);
	
        for(int i = 0 ; i < destinations_vect.size(); i++){
            for(int j = 0 ; j < time_distribution_vect[i] ; j++){
                vector< pair< double, double > > temp;
                for(int k = 0 ; k < position_vect.size(); k++){
                    double velocity_x = (destinations_vect[i].first - output_vect[output_vect.size()-1][k].first) / time_distribution_vect[i];
                    double velocity_y = (destinations_vect[i].second - output_vect[output_vect.size()-1][k].second) / time_distribution_vect[i];
                    velocity_x = add_random_noise(velocity_x, noise_for_deer);
                    velocity_y = add_random_noise(velocity_y, noise_for_deer);
                    double p_x = output_vect[output_vect.size()-1][k].first + velocity_x;
                    double p_y = output_vect[output_vect.size()-1][k].second + velocity_y;
                    temp.push_back({p_x, p_y});
                }
                output_vect.push_back(temp);
            }
        }
        
        return output_vect;

//        for(int i = 0 ; i < output_vect.size(); i++){
//        	for(int j = 0 ; j < output_vect[i].size(); j++){
//        		cout << output_vect[i][j].first << " " << output_vect[i][j].second << " -- ";
//			}
//			cout << endl;
//		}
}

int main(){
	srand (time(NULL));
	ofstream myfile;
  myfile.open ("example.txt");
  //myfile << "Writing this to a file.\n";
  
	int dest, deer, time;
	vector<pair<double, double > > dest_vect, deer_vect;
	vector< vector < pair < double, double> > > output;
	double x, y;
	cin >> dest >> deer >> time;
	
	for(int i = 0 ; i < dest ; i++){
		cin >> x >> y;
		dest_vect.push_back({x,y});
	}
	 
	x = -32.330207;
	y = 121.797586;
	
	for(int i = 0 ; i < deer; i++){
	//	cin >> x >> y;
		deer_vect.push_back({x,y + 0.1 * i});
	}
	
	output = swarm(deer_vect, dest_vect, time);
	
	myfile << "[";
	
	for(int i = 0 ; i < output.size(); i++){
		for(int j = 0 ; j < output[i].size(); j++){
			myfile <<"{" << endl;
			myfile << '"' << "id" << '"' << ": " << '"' << j << '"' << "," << endl;
			myfile << '"' << "type" << '"' << ":" << '"' << "animal" << '"' << "," << endl;
			myfile << '"' << "lat" << '"' << ":" << setprecision(7) << fixed << output[i][j].first << "," << endl;
			myfile << '"' << "long" << '"' << ":" << setprecision(7) << fixed << output[i][j].second << "," << endl;
			myfile << "}," << endl; 
						
		}
	}
	myfile << "];" << endl;
	myfile.close();
}
