#!/bin/bash

set -e
set -u


#------------------------------------------------------------------------------------
#		Tools
#------------------------------------------------------------------------------------

function installWorkspaceMain()
    {
     pushd .>/dev/null

    local readonly IS_ARM=$1

    if $IS_ARM
    then
        echo "ARM detected"
        compile_install_opt_api_ARM
    else
        compile_install_opt_api
    fi

    symlink_opt_api
    workspace_symlink_ext

    if [[ "$(uname)" == "Linux" ]]
	then
        security_opt_api
    fi
  
    popd >/dev/null
    }

function compile_install_opt_api()
	{
    pushd .>/dev/null

    if [[ "$(uname)" == "Linux" ]]
    then
		    if [[ $USER != "root" ]]
		    then
			    echo ""
			    echo "Error : this script must be launch in sudo "
			    echo ""
			    exit 1
			    
		    fi
		    
		    #gcc & intel
		    cbicc gcc installworkspace
		    cbicc java installworkspace
		    
    else
		    #visual & intel & mingw
		    cbicc visual installworkspace
		    cbicc java installworkspace
		    #echo ""
    fi

    popd >/dev/null
    }

function compile_install_opt_api_ARM()
    {
    if [[ $USER != "root" ]]
    then
	    echo ""
	    echo "Error : this script must be launch in sudo "
	    echo ""
	    exit 1
	    
    fi
		    
    cbicc gcc installworkspaceARM
    cbicc java installworkspace
    }


function symlink_opt_api()
    {
     pushd .>/dev/null

    cbicc gcc symlinkExtBinAll

     popd >/dev/null
    }


# pour tous les projets
function workspace_symlink_ext()
    {
     pushd .>/dev/null

    cd ..
    WORKSPACE_ROOT=$(pwd)

    cd ./BUILDER/makefile/private/script/workspace_auto

    ./workspace_symlink_ext.sh ${WORKSPACE_ROOT}

     popd >/dev/null
    }

function security_opt_api()
	{
	local readonly DESTINATION=/opt/api
	
	chown -R root:cbi-dev $DESTINATION
	
	chmod -R u+rwx $DESTINATION
	chmod -R g+rx $DESTINATION
    chmod -R g-w $DESTINATION
	chmod -R o-rwx $DESTINATION

    echo ""
    echo "chown -R root:cbi-dev $DESTINATION"
    echo "chmod -R u+rwx $DESTINATION"
    echo "chmod -R g+rx $DESTINATION"
    echo "chmod -R g-w $DESTINATION"
    echo "chmod -R o-rwx $DESTINATION"
    echo ""
	}

#------------------------------------------------------------------------------------
#		main
#------------------------------------------------------------------------------------

#Input : 
#       true si arm
#       false sinon
#         
#       Note : list project is define in DataProject.mk

#usage debug
#
#       sudo ./install_workspace.sh $IS_ARM > debug.txt
#       cat ./debug.txt | grep find

IS_ARM=$1
installWorkspaceMain $IS_ARM

#------------------------------------------------------------------------------------
#		end
#------------------------------------------------------------------------------------
