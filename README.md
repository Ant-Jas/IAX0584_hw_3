# IAX0584_hw_3
(IAX0584) Programmeerimine II homework 3 - Local weather forecast  
Data provided by Keskkonnaagentuur (ilmateenistus.ee).

# Dependencies
libcurl,
libxml2

# Compiling
Make sure you are in the same directory as the Makefile file.

```shell
user@sys:~$ make all
```
Delete all the object files and the compiled program:

```shell
user@sys:~$ make fclean
```

Delete all the object files:

```shell
user@sys:~$ make clean
```

# Supported arguments
0. No arguments
```shell
user@sys:~$ ./weather_forecast.out
```
Displays observation data for locations added as favorite.  
If user has no favorites, info about the following locations is displayed:  
    Tallinn-Harku  
    Tartu-Tõravere  
    Narva

1. Add a location
```shell
user@sys:~$ ./weather_forecast.out --add_location "Kuressaare linn"
```
Adds the location Kuressaare linn as a favorite. For locations consisting of a  
single word quotation marks are not required.

2.  Remove a location
```shell
user@sys:~$ ./weather_forecast.out --rm_location "Kuressaare linn"
```
Removes the location Kuressaare linn from favorites. For locations consisting  
of a single word quotation marks are not required.

3. Display forecast
```shell
user@sys:~$ ./weather_forecast.out --forecast
```
Displays the date, minimum and maximum day and night temperatures for all the  
days available in the forecast.
