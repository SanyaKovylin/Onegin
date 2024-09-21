# Onegin

The Onegin program aims to sort the poem of Alexander Sergeevich Pushkin "Evgeniy Onegin"

First downloaded, you should run the console in that folder, where it was downloaded. Then run the make command. After that in your directory will be made the Build folder. Then you can run the "Sorter.exe" with console flags -r -o and -s(Learn more from --help). Then you will get the file "sorted.exe" in "Build" folder where will be the sorted origin of "Evgeniy Onegin". 

# About useful functions:

You can find some ones you can use in your projects. Such as:

unisorter.cpp:

>StrSorter which is actually a qsort function prototype. So you can use it an mosify.
>
>memswap  which is vectorized memory swap of any type variable.
 
utils.cpp:

>cmpstr which is a string comparator by void pointers
>
>revcmpstr which is a string comparator fro the end

They both ignore the previous and the following syntax marks


