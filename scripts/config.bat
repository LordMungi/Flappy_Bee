echo -Running inital configuration-

set path=%~1
set out=%~2

echo using %path%
echo and %out%

cd %path%

echo step 1

if not exist %out%\ (
	echo copying library dependencies at
	echo %path%lib\
	copy "%path%lib\sigil-vc2015-win64\lib\*.dll" "%out%" /y

	echo creating resource folder at
	echo %path%res\
	echo audio
	copy "%path%res\audio\" "%out%res\audio\" /y
	echo fonts	
	copy "%path%res\fonts\" "%out%res\fonts\" /y
	echo sprites
	copy "%path%res\sprites\" "%out%res\sprites\" /y

	echo crating configs and data
	copy "%path%config\" "%out%config\" /y
	copy "%path%data\" %out%data\" /y
)

echo Done!