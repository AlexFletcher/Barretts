This GitHub repository contains Chaste code for simulating Barrett's 
esophagus segment establishment.

**Files in this repository**

The repository contains three folders - apps, src, and apps. 

You can ignore the <apps> folder for now.

The <src> folder contains a number of .hpp and .cpp files defining classes that are
required to compile the test suite(s) for this project.

The <test> folder contains test suite(s) for this project - the code that running 
simulations.

At the moment, there is a single test suite, called TestBarrettsFirstAttempt.hpp, 
which contains some first steps toward implementing your desired simulation of 
Barrett's esophagus segment establishment via crypt fission. 


**Coding preliminaries**

Chaste is written in C++. A decent guide to this programming language is the 
following book, co-written by one of the Chaste developers:

http://www.springer.com/gp/book/9781447127352


**Introduction to cell-based Chaste**

Chaste is an open-source C++ library and a set of test suites for 
computational simulations in the domain of biology. The most recent public 
release of Chaste, version 3.4, was released in February 2016 under the BSD 
licence. In July 2016 development of Chaste transitioned from a svn to a git 
version control system, making it much easier to external users to clone and 
use the latest development branch of the code.

While Chaste is a generic extensible library, a major focus of software 
development to date has been on cell-based modelling of cell populations, 
with application to tissue morphogenesis, homeostasis and carcinogenesis. 
The aim of this part of Chaste, 'cell-based Chaste', is to develop a 
computational framework that bridges across the subcellular, cellular and 
tissue scales within a single, generic modelling framework. 

We employ a multiscale modelling framework comprising up to three 
interlinked modules: a model of cellular behaviour (e.g. progress through 
the cell cycle); a model of the movement and mechanical interaction between 
cells (e.g. a vertex model); and a model of the transport of key signalling 
molecules (e.g. a reaction-diffusion model).


**User support**

The Chaste developer wiki (https://chaste.cs.ox.ac.uk) contains a lot of 
information on how to install and run Chaste. In particular, you can find 
several 'user tutorials', which provide walkthroughs on how to simulate 
cell-based models such as vertex models within Chaste using existing or new 
functionality, at https://chaste.cs.ox.ac.uk/trac/wiki/UserTutorials. 

For general questions about Chaste, for example on installation or set-up, 
you can email me directly (a.g.fletcher@sheffield.ac.uk) or else email the 
users mailing list. To subscribe to the list, follow the instructions at 
https://web.maillist.ox.ac.uk/ox/subscribe/chaste-users). You can then send 
an email with your question to chaste-users@maillist.ox.ac.uk. A third 
option is to join the ChasteTeam channel on Slack; if you are interested, 
then I can invite you as a new member to the channel.


**How to install Chaste**

Chaste is supported on Linux/Unix platforms and our recommended route for 
Windows and OSX users is to install Chaste on a virtual machine running 
Ubuntu Linux. However, several developers and users have successfully 
installed Chaste natively on OSX. Below, I described each of these 
approaches.

*Installing Chaste in an Ubuntu virtual machine*

1. Download and install VirtualBox. To do this, go to 
https://www.virtualbox.org and select the correct version for your operating 
system. You can find plenty of online guides for how to install an Ubuntu 
virtual machine in OSX using VirtualBox, e.g. 
http://www.simplehelp.net/2015/06/09/how-to-install-ubuntu-on-your-mac.

2. Once you have set up your Ubuntu virtual machine, follow the instructions 
at https://chaste.cs.ox.ac.uk/trac/wiki/InstallGuides/UbuntuPackage to 
install Chaste in it. Follow steps 1, 2b ("For Code DEVELOPERS") and 3 on 
that page.

3. Install the latest master branch of the Chaste Git repository by typing 
the following at the command line, in a directory of your choosing:

git clone https://chaste.cs.ox.ac.uk/git/chaste.git chaste

4. Install the Boost program options package:

apt-get install libboost-program-options-dev

5. To make sure cmake won't re-link every time you build, remove line 34 
( dummy) of the file global/CMakeLists.txt.

6. Install ccmake: 

apt-get install cmake-curses-gui

7. Still at the command line, navigate to the chaste directory,
and type:

mkdir ../chaste_build
cd ../chaste_build
ccmake ../chaste

This will open a graphical user interface in your terminal. Using the arrow 
keys, scroll down to the variable Chaste_UPDATE_PROVENANCE and set this to 
OFF (this will slightly speed up compilation by preventing one source code 
file that normally contains the time at which compilation started and thus 
changes on every build, from being regenerated). Also set CMAKE_BUILD_TYPE 
to RELEASE (this will optimise the build, speeding up simulations). Then 
type c to configure. Once cmake has finished configuring, type e to exit the 
helper and then g to generate. When this process is complete, you will be 
taken back to the standard terminal.

8. To check that Chaste compiles and runs on your machine, from the 
chaste_build directory type:

make -j4 cell_based

to build the cell-based component of Chaste, replacing '4' with the number 
of cores your machine has. Once this is complete, check everything works by 
running the cell-based test pack:

ctest -j4 –L cell_based

Some tests will be listed with (Not run) after them; this is expected, as we 
did not build tests from the cardiac component.

9. Install Paraview to be able to visualize results of cell-based simulation 
in VTK format. See e.g. the instructions at 
https://chaste.cs.ox.ac.uk/trac/wiki/InstallParaview.

*Installing Chaste in OSX*

There have been a few attempts to document the installation of Chaste in 
different versions of OSX. For further details, see: 

https://chaste.cs.ox.ac.uk/trac/wiki/InstallGuides/ChasteInstallationOnMountainLion
https://chaste.cs.ox.ac.uk/trac/wiki/InstallGuides/ChasteInstallationOnOSXYosemite


**Writing and running Chaste code**

For ease of navigating the Chaste libraries, consider installing Eclipse, 
Visual Studio Code or some other integrated development environment. If 
using Eclipse, you can import Chaste by clicking File->Import... then 
selecting "Existing Projects into Workspace". Navigate to [path/to/Chaste].


**SEB Cell Symposium tutorial**

The online tutorial that you went through during the SEB Cell Symposium 
Chaste day can be found here:

https://chaste.cs.ox.ac.uk/trac/wiki/SEBCellSymposiumChasteWorkshop

It includes links to other tutorials that explain how to write new source 
code and run new test suites within the Chaste framework.


**User project**

The following guide explains our recommended strategy for how to create and 
use a git repository to store individual work that makes use of the Chaste 
code and build system. We use the term 'user project' to refer to such a 
repository. You can find similar information at 
https://chaste.cs.ox.ac.uk/trac/wiki/InstallGuides/CheckoutUserProject.
NOTE: For current purposes, you don't need to do steps 1 and 2, since I've 
already created a user project 'Barretts' in my GitHub repository 
'AlexFletcher', so you can jump to step 3.

1. If you want to create a new user project, then start by forking the 
template user project git repository located at ​
https://github.com/Chaste/template_project. To do this, navigate to this 
repository in your browser and click 'Fork' in the top-right corner of the 
page. 

2. On your fork, change the repository name from template_project to 
whatever you want. To do this, navigate to the forked repository in your 
browser and click 'Settings', type the new name of the repository under the 
'Repository Name' heading, and click 'Rename'.

3. Clone your fork. To do this from the command line, run

git clone https://github.com/[RepoName]/[UserProjectName].git [UserProject]

where you should replace [RepoName] with the name of your own git repository 
and [UserProjectName] with the name you chose for the user project 
repository in step 2.

4. Navigate to your cloned user project repository at the command line, and 
run

python setup_project.py

5. Create a symbolic link to your user project repository in the Chaste 
projects folder. To do this, navigate to the Chaste source folder at the 
command line and run

cd projects
ln -s [path/to/UserProject]

where you should replace [path/to/UserProject] with the location of your 
cloned user project repository (see step 3).

6. To check that your user project compiles correctly, at the command line 
navigate to your Chaste build folder and run

ccmake [path/to/Chaste]

where you should replace [path/to/Chaste] with the location of your Chaste 
source folder. Type c to configure; when this process is complete, type e to 
exit the configuration. You should find that three additional lines have 
been added to cmake. These are Chaste_ENABLE_project_[UserProjectName]_APPS, 
Chaste_ENABLE_project_[UserProjectName]_INSTALL and 
Chaste_ENABLE_project_[UserProjectName]_TESTING. Type c to configure once 
more, then e to exit and g to generate. When this process is complete, type

make TestHelloRunner
ctest -R ^TestHello$

and check that TestHello passes.

