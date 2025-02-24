int interpolate(mandel_pic old_pic, double x, double y) {
    //To force computation of new pixels
    if (random() < RAND_MAX*REFRESH_PROB)
        return -1;
    
    //Outside the previous image
    //or equal, to avoid border effects in the 4 neighbors interpolation
    if (x < old_pic.Xmin) 
        return -1;
    if (x > old_pic.Xmax) 
        return -1;
    if (y < old_pic.Ymin) 
        return -1;
    if (y > old_pic.Ymax)
        return -1;
    
    double val;
    double xindex, yindex;
    int xi, yi;

    //Projection of new coordinates in the old 
    xindex = (x - old_pic.Xmin)/old_pic.pixwidth; //Between 0-width
    yindex = (y - old_pic.Ymin)/old_pic.pixwidth; //Between 0-height
    xi = xindex;
    yi = yindex;

    //For closest point,
    return old_pic.convrg[xi + old_pic.width*(old_pic.width - yi)];

    //Interpolation with 4 neighbors
    //To complete
}

