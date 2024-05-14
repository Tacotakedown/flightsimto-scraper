## required libs:

`cpprestsdk` - install with vcpkg `vcpkg install cpprestsdk cpprestsdk:x64-windows`

## building:

requirements: `vs 2022`, `vcpkg`, `cmake`

`git clone https://github.com/Tacotakedown/flightsimto-scraper.git`

`cd flightsimto-scraper`

`cmake --preset=default`

`cmake --build build`

## usage 
`FlightSimToScraper --link="https://flightsim.to/file/12408/msfs-native-c-17-globemaster"`