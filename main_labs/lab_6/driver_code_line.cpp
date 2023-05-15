#include "line_intersection.cpp"

int main()
{
    priority_queue<l_segment, vector<l_segment>, Comparex> pq;
    int n, x, y, x1, y1, axis;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y >> x1 >> y1 >> axis;
        pq.push(l_segment(point(x, y), point(x1, y1), axis));
    }
    showpq(pq);
    AVLTree tree;
    priority_queue<l_segment, vector<l_segment>, Comparex> vertical;
    while (!pq.empty())
    {
        l_segment l = pq.top();
        pq.pop();
        if (l.axis == 0)
        {
            tree.insert(l);
        }
        else
        {
            vertical.push(l);
        }
    }

    showpq(vertical);
    while (!vertical.empty())
    {
        l_segment l = vertical.top();
        vertical.pop();
        tree.CheckIntersection(l);
    }
    return 0;
}