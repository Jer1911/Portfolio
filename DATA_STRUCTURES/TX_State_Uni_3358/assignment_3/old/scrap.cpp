int findmin(struct node *start)
{
    int min=start->data;
    while(start!=NULL)
    {
        if(start->data < min)
           min = start->data;
        start=start->link;
    }
    return min;
}/*End of findmin()*/

