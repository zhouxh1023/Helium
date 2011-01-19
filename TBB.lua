require "Base"

--[[

NOTE:
We set cwd to be the location of make because gmake on windows (or mingw) will auto-complete the path to make to a full path
if this full path has spaces then tbb's make logic will fail.  -C will cwd to the tbb root before it starts processing
This is mainly to support building from user folders in XP -Geoff

--]]

Helium.BuildTBB = function()

	local cwd = os.getcwd()

	if os.get() == "windows" then

		if not os.getenv("VCINSTALLDIR") then
			print("VCINSTALLDIR is not detected in your environment")
			os.exit(1)
		end
				
		os.chdir( "Utilities/Win32" );

		local result
        if string.find( os.getenv("PATH"), "x64" ) then
            result = os.execute( "cmd.exe /c \"call \"%VCINSTALLDIR%\"\\vcvarsall.bat x86_amd64 && make.exe -C ../../Dependencies/tbb tbb arch=intel64\"" )
            if result ~= 0 then os.exit( 1 ) end
        else
            result = os.execute( "cmd.exe /c \"call \"%VCINSTALLDIR%\"\\vcvarsall.bat x86 && make.exe -C ../../Dependencies/tbb tbb arch=ia32\"" )
            if result ~= 0 then os.exit( 1 ) end
        end
	else
		print("Implement support for " .. os.get() .. " to BuildTBB()")
		os.exit(1)
	end

	os.chdir( cwd )

end

Helium.CleanTBB = function()

	local cwd = os.getcwd()

	local files = {}
	
	if os.get() == "windows" then

		if not os.getenv("VCINSTALLDIR") then
			print("VCINSTALLDIR is not detected in your environment")
			os.exit(1)
		end
				
		os.chdir( "Utilities\\Win32" );

		local result
        if string.find( os.getenv("PATH"), "x64" ) then
            result = os.execute( "cmd.exe /c \"call \"%VCINSTALLDIR%\"\\vcvarsall.bat x86_amd64 && make.exe -C ../../Dependencies/tbb clean arch=intel64\"" )
            if result ~= 0 then os.exit( 1 ) end
        else
            result = os.execute( "cmd.exe /c \"call \"%VCINSTALLDIR%\"\\vcvarsall.bat x86 && make.exe -C ../../Dependencies/tbb clean arch=ia32\"" )
            if result ~= 0 then os.exit( 1 ) end
        end
	else
		print("Implement support for " .. os.get() .. " to CleanTBB()")
		os.exit(1)
	end

	os.chdir( cwd )

end

Helium.PublishTBB = function( bin )

	local files = {}
	
	if _ACTION == "vs2005" then
        if string.find( os.getenv("PATH"), "x64" ) then		
            files[1] = { file="tbb_debug.dll",		source="Dependencies/tbb/build/windows_intel64_cl_vc8_debug",	    target=bin .. "/x64/Debug" }
            files[2] = { file="tbb_debug.pdb",		source="Dependencies/tbb/build/windows_intel64_cl_vc8_debug",	    target=bin .. "/x64/Debug" }
            files[3] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_intel64_cl_vc8_release",	    target=bin .. "/x64/Intermediate" }
            files[4] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_intel64_cl_vc8_release",	    target=bin .. "/x64/Intermediate" }
            files[5] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_intel64_cl_vc8_release",	    target=bin .. "/x64/Profile" }
            files[6] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_intel64_cl_vc8_release",	    target=bin .. "/x64/Profile" }
            files[7] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_intel64_cl_vc8_release",	    target=bin .. "/x64/Release" }
            files[8] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_intel64_cl_vc8_release",	    target=bin .. "/x64/Release" }
        else
            files[1] = { file="tbb_debug.dll",		source="Dependencies/tbb/build/windows_ia32_cl_vc8_debug",		    target=bin .. "/x32/Debug" }
            files[2] = { file="tbb_debug.pdb",		source="Dependencies/tbb/build/windows_ia32_cl_vc8_debug",		    target=bin .. "/x32/Debug" }
            files[3] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_ia32_cl_vc8_release",        target=bin .. "/x32/Intermediate" }
            files[4] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_ia32_cl_vc8_release",        target=bin .. "/x32/Intermediate" }
            files[5] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_ia32_cl_vc8_release",        target=bin .. "/x32/Profile" }
            files[6] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_ia32_cl_vc8_release",        target=bin .. "/x32/Profile" }
            files[7] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_ia32_cl_vc8_release",        target=bin .. "/x32/Release" }
            files[8] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_ia32_cl_vc8_release",        target=bin .. "/x32/Release" }
        end
	elseif _ACTION == "vs2008" then
        if string.find( os.getenv("PATH"), "x64" ) then
            files[1] = { file="tbb_debug.dll",		source="Dependencies/tbb/build/windows_intel64_cl_vc9_debug",	    target=bin .. "/x64/Debug" }
            files[2] = { file="tbb_debug.pdb",		source="Dependencies/tbb/build/windows_intel64_cl_vc9_debug",	    target=bin .. "/x64/Debug" }
            files[3] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_intel64_cl_vc9_release",	    target=bin .. "/x64/Intermediate" }
            files[4] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_intel64_cl_vc9_release",	    target=bin .. "/x64/Intermediate" }
            files[5] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_intel64_cl_vc9_release",	    target=bin .. "/x64/Profile" }
            files[6] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_intel64_cl_vc9_release",	    target=bin .. "/x64/Profile" }
            files[7] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_intel64_cl_vc9_release",	    target=bin .. "/x64/Release" }
            files[8] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_intel64_cl_vc9_release",	    target=bin .. "/x64/Release" }
        else
            files[1]  = { file="tbb_debug.dll",		source="Dependencies/tbb/build/windows_ia32_cl_vc9_debug",		    target=bin .. "/x32/Debug" }
            files[2]  = { file="tbb_debug.pdb",		source="Dependencies/tbb/build/windows_ia32_cl_vc9_debug",		    target=bin .. "/x32/Debug" }
            files[3]  = { file="tbb.dll",			source="Dependencies/tbb/build/windows_ia32_cl_vc9_release",        target=bin .. "/x32/Intermediate" }
            files[4]  = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_ia32_cl_vc9_release",        target=bin .. "/x32/Intermediate" }
            files[5]  = { file="tbb.dll",			source="Dependencies/tbb/build/windows_ia32_cl_vc9_release",        target=bin .. "/x32/Profile" }
            files[6]  = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_ia32_cl_vc9_release",        target=bin .. "/x32/Profile" }
            files[7]  = { file="tbb.dll",			source="Dependencies/tbb/build/windows_ia32_cl_vc9_release",        target=bin .. "/x32/Release" }
            files[8]  = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_ia32_cl_vc9_release",        target=bin .. "/x32/Release" }
        end
	elseif _ACTION == "vs2010" then 
        if string.find( os.getenv("PATH"), "x64" ) then
            files[1] = { file="tbb_debug.dll",		source="Dependencies/tbb/build/windows_intel64_cl_vc10_debug",	    target=bin .. "/x64/Debug" }
            files[2] = { file="tbb_debug.pdb",		source="Dependencies/tbb/build/windows_intel64_cl_vc10_debug",	    target=bin .. "/x64/Debug" }
            files[3] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_intel64_cl_vc10_release",	target=bin .. "/x64/Intermediate" }
            files[4] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_intel64_cl_vc10_release",	target=bin .. "/x64/Intermediate" }
            files[5] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_intel64_cl_vc10_release",	target=bin .. "/x64/Profile" }
            files[6] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_intel64_cl_vc10_release",	target=bin .. "/x64/Profile" }
            files[7] = { file="tbb.dll",			source="Dependencies/tbb/build/windows_intel64_cl_vc10_release",	target=bin .. "/x64/Release" }
            files[8] = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_intel64_cl_vc10_release",	target=bin .. "/x64/Release" }
        else
            files[1]  = { file="tbb_debug.dll",		source="Dependencies/tbb/build/windows_ia32_cl_vc10_debug",		    target=bin .. "/x32/Debug" }
            files[2]  = { file="tbb_debug.pdb",		source="Dependencies/tbb/build/windows_ia32_cl_vc10_debug",		    target=bin .. "/x32/Debug" }
            files[3]  = { file="tbb.dll",			source="Dependencies/tbb/build/windows_ia32_cl_vc10_release",	    target=bin .. "/x32/Intermediate" }
            files[4]  = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_ia32_cl_vc10_release",	    target=bin .. "/x32/Intermediate" }
            files[5]  = { file="tbb.dll",			source="Dependencies/tbb/build/windows_ia32_cl_vc10_release",	    target=bin .. "/x32/Profile" }
            files[6]  = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_ia32_cl_vc10_release",	    target=bin .. "/x32/Profile" }
            files[7]  = { file="tbb.dll",			source="Dependencies/tbb/build/windows_ia32_cl_vc10_release",	    target=bin .. "/x32/Release" }
            files[8]  = { file="tbb.pdb",			source="Dependencies/tbb/build/windows_ia32_cl_vc10_release",	    target=bin .. "/x32/Release" }
        end
	end
	
	Helium.Publish( files )

end