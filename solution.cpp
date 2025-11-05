#include <bits/stdc++.h>
using namespace std;

int main() {
    int A, N, M;
    
    // Read A (number of Guardians)
    cin >> A;
    
    // Read N (number of nodes)
    cin >> N;
    
    // Read B array (distances between consecutive nodes)
    vector<long long> B(N - 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> B[i];
    }
    
    // Read M (number of thieves)
    cin >> M;
    
    // Read C array (thief node and arrival time)
    vector<vector<long long>> C(M, vector<long long>(2));
    for (int i = 0; i < M; i++) {
        cin >> C[i][0] >> C[i][1];
    }
    
    // Calculate cumulative distances from node 1 to each node
    vector<long long> dist(N + 1, 0);
    for (int i = 1; i < N; i++) {
        dist[i + 1] = dist[i] + B[i - 1];
    }
    
    // Calculate effective departure time for each thief
    // If a guardian departs at time t, it reaches node j at time t + dist[j]
    // For thief arriving at node j at time T, effective time = T - dist[j]
    vector<long long> effectiveTime(M);
    for (int i = 0; i < M; i++) {
        int node = C[i][0];
        long long arrivalTime = C[i][1];
        effectiveTime[i] = arrivalTime - dist[node];
    }
    
    // Sort thieves by effective time
    vector<int> indices(M);
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(), [&](int i, int j) {
        return effectiveTime[i] < effectiveTime[j];
    });
    
    // Use multiset to track Guardian departure times
    multiset<long long> guardianTimes;
    
    long long totalWaiting = 0;
    
    for (int idx : indices) {
        long long eff = effectiveTime[idx];
        int node = C[idx][0];
        long long arrivalTime = C[idx][1];
        
        if (guardianTimes.size() < A) {
            // Assign a new Guardian departing at this effective time
            guardianTimes.insert(eff);
            // Waiting time = 0 (Guardian arrives exactly when thief arrives)
        } else {
            // Find the Guardian with earliest departure time
            auto it = guardianTimes.begin();
            long long guardianDept = *it;
            
            // Guardian arrives at: guardianDept + dist[node]
            // Waiting time = (guardianDept + dist[node]) - arrivalTime
            long long guardianArrival = guardianDept + dist[node];
            long long waiting = guardianArrival - arrivalTime;
            
            totalWaiting += waiting;
            
            // Remove this Guardian and reassign with new departure time
            guardianTimes.erase(it);
            guardianTimes.insert(eff);
        }
    }
    
    cout << totalWaiting << endl;
    
    return 0;
}
