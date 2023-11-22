//Name: Gregory Grullon
//Course: CSCI-135
//Instructor: Tong Yi
//Assignment: Lab 10

#include <iostream>
using namespace std;

/*
(Enum types work as sets of named values. A variable of 
type Genre can assume any of the values listed in the curly 
braces, example: Genre myFavorite = COMEDY;)
*/

enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

class Time {    //keyword class and classname Time
public:     //speciier
    int h;  //(hours)           //variables
    int m;  //(minutes)
}; //end of class with semicolon

class Movie {
    public:
        string title;
        Genre genre;    //only one genre per movie
        int duration; //in minutes
};

class TimeSlot {
    public: 
        Movie movie;    //what movie
        Time startTime; //when it starts
};

void printTime(Time time); //Just checks current time

int minutesSinceMidnight(Time time);  //converts time into mins

int minutesUntil(Time earlier, Time later); //checks interval between earlier and later

Time addMinutes(Time time0, int min);   //adds minutes to current time

void printMovie(Movie mv);  //prints title, genre, duration
//Ex: Black Panther ACTION (134 min) [starts at 12:15, ends by 14:29]

void printTimeSlot(TimeSlot ts);

TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie);

//Function lets us know if two time slots overlap
bool timeOverlap(TimeSlot ts1, TimeSlot ts2);

int main(){
    Movie movie1 = {"Joe Bob The Movie", ROMANCE, 120};
    Movie movie2 = {"What it Do?", THRILLER, 100};

    TimeSlot Morning = {movie1, {10, 10}};
    TimeSlot Afternoon = {movie2, {12, 10}};

    bool overlap = timeOverlap(Morning, Afternoon);

    if(overlap){
        cout << "true" << endl;
    }
    else{
        cout << "false" << endl;
    }
    return 0;
}

bool timeOverlap(TimeSlot ts1, TimeSlot ts2){
    int ts1_mins = minutesSinceMidnight(ts1.startTime); //converts start to mins
    int ts2_mins = minutesSinceMidnight(ts2.startTime); //converts start to mins
    TimeSlot earlier;   
    //We are using this object from the class timeSlot to see which 
    //timeslot is earlier. (Starts first)
    if(ts1_mins < ts2_mins){ //when ts1 has less mins so its earlier
        earlier = ts1;
    }
    else{ //when ts2 has less mins so its earlier
        earlier = ts2;
    }

    int diff = ts1_mins - ts2_mins;
    //We calculate the difference so we can see duration betweem
    // the two movies. if the duration of the earlier movie is less
    //than the difference of the 2 then there is an overlap.

    if(diff < 0){ //keeps the value positive. so when comparing
    //there are no errors.

        diff = -diff;
    }
    if(earlier.movie.duration > diff)
    //Checks to see if the earlier movie has a greater time duration than
    //difference between the two movies. Which would mean there is an overlap.
    {
        return true;
    }
    else{ 
    //if the earlier movie has a less amount of duration than the diff
    //between the two movies there is no overlap.
        return false;
    }

}

TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie){
    Time endTime = addMinutes(ts.startTime, ts.movie.duration);
    //ts.startTime would represent the startTime for morning. 
    //and ts.movie.duration would represent "Morning" but its
    //duration which is 120 mins.
    //So endTime now = 16:10
    TimeSlot new_ts = {nextMovie, endTime};
    //NextMovie would be "What it do" and the startTime now for
    //it would be the endTime for Morning. 
    return new_ts;
}

void printTimeSlot(TimeSlot ts){
    Time endTime = addMinutes(ts.startTime, ts.movie.duration);
    //ts.startTime comes from the timeslot class to represent the
    //start of the movie. While ts.movie.duration starts from timeslot
    //goes to movie and take the duration of that specific movie and
    //uses it to add minutes to the movie. Which helps us get our endTime.
    printMovie(ts.movie);       //prints title, genre, and duration
    cout << " [starts at "; 
    printTime(ts.startTime);    //Print Start Time
    cout << ", ends by "; 
    printTime(endTime);         //Print End Time
    cout << "]" << endl;
}   

//This function down below prints the title, genre, and duration.
void printMovie(Movie mv){
    string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    cout << mv.title << " " << g << " (" << mv.duration << " min)";
}

void printTime(Time time) {
    cout << time.h << ":" << time.m;
    //remeber when we use time.h we are reffering to that data member
    //within the class Time.
}

int minutesSinceMidnight(Time time){
    int minutes_since_midnight = (time.h * 60) + time.m;
    //The varaible here converts the time.h or the objects hours we 
    //are using for the function to turn into minutes. Then we just
    //add the remaining minutes from the users input for mins.
    return minutes_since_midnight;
}

int minutesUntil(Time earlier, Time later){
    int time_passed = minutesSinceMidnight(later) - minutesSinceMidnight(earlier);
    //We subtract the later time with the earlier time minutes so we can
    //see the amount of minutes between the two times.
    return time_passed;
}

Time addMinutes(Time time0, int min){
    int new_mins = minutesSinceMidnight(time0) + min;
    Time new_time; //time obj that stores result
    new_time.h = (new_mins/60); //gets new hours by division
    new_time.m = (new_mins%60); //gets new mins by finding remainder

    //if hours exceeds 23 hours and minutes is greater than or equal to 
    //zero it will cap the time to 23:59 for same day results.
    if(new_time.h >= 24 && new_time.m >= 0){
        new_time.h = 23;
        new_time.m = 59;
    }

    return new_time;
}

/* Task D.
int main(){
    Movie movie1 = {"Joe Bob The Movie", ROMANCE, 120};
    Movie movie2 = {"What it Do?", THRILLER, 100};

    TimeSlot Morning = {movie1, {14, 10}};
    So here we are using the scheduleAfter function to schedule
    the next movie right after "Morning" is over. What happens is 
    that we are calculating the start time for movie2 by adding the 
    duration(mins of movie1) to the begining of morning. It starts at
    14:10 and we add 120 mins to it so we get 16:10. Which is then
    stored into "Afternoon."
    TimeSlot Afternoon = scheduleAfter(Morning, movie2);

    printTimeSlot(Morning);
    printTimeSlot(Afternoon);

    return 0;
}
/* Task C.
int main(){
    Movie movie1 = {"Back to the Future", COMEDY, 116};
    Movie movie2 = {"Black Panther", ACTION, 134};
    Movie movie3 = {"Minions", COMEDY, 119};
    Movie movie4 = {"Sonic The HedgeHog", ACTION, 140};

    //Our timeslots are meant to represent the different movies
    //and the timezones when they will be shown.
    TimeSlot morning = {movie1, {9, 15}};  
    TimeSlot daytime = {movie2, {12, 15}}; 
    TimeSlot evening = {movie2, {16, 45}}; 
    TimeSlot night = {movie4, {20, 0}};
    TimeSlot midnight = {movie3, {22, 0}};

    printTimeSlot(morning); //timeslot object being used is morning
    //and morning represents movie1 which is "Back to the Future",
    //COMEDY, 116(mins);
    printTimeSlot(daytime);
    printTimeSlot(evening);
    printTimeSlot(night);
    printTimeSlot(midnight);
    return 0;
}
*/
/*
int main(){
    int new_min, hr1, min1;

    cout << "Enter first time: ";
    cin >> hr1 >> min1; //current hour and mins on the clock

    Time current = {hr1, min1};
    //h and m have the value from user inputs.

    cout << "Enter number of mins to add: ";
    cin >> new_min; //user input for added mins

    Time new_time = addMinutes(current, new_min);
    //remember to create the new object for the newtime so we can
    //then print it out.

    cout << "New time after adding " << new_min << " minutes: ";
    printTime(new_time);  //We are calling the printTime func to see how much time was added
    cout << endl;

    return 0;
}

*/

/* For Task A.
int main(){
    int min1, min2, hr1, hr2;

    cout << "Enter first time: ";
    cin >> hr1 >> min1;
    cout << "Enter second time: ";
    cin >> hr2 >> min2;

    Time earlier = {hr1, min1};
    Time later = {hr2, min2};

    int bog = minutesSinceMidnight(earlier);    //if 10:30 we get 630 mins
    int gob = minutesSinceMidnight(later);      //if 13:40 we get 820 mins
    int Z = minutesUntil(earlier, later);       //Interval between both times

    cout << "These moments of time are " << bog << " and " << gob << 
    " minutes after midnight." << endl;
    cout << "The interval between them is " << Z << " minutes." << endl;
    
    Alternatively, we can create an object and immediately 
    initialize all its fields with the following literal syntax 
    (the order of values in curly braces is important):
    //Time t = {17, 45};
    //Time = 17:45

    return 0;
}

*/

/*
Time morningLecture = {8, 10};

Time myAlarm;              // make another variable

myAlarm = morningLecture;    // copying

printTime(morningLecture);   // will print 8:10
cout << endl;
printTime(myAlarm);        // will print 8:10 as well
                           // You may be late for the class tho
*/
