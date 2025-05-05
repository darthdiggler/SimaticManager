# Load the DLL
#Add-Type -Namespace TestProjectV3 -Name NativeMethods -MemberDefinition @"
    #[DllImport("C:\\Projects\\VS_Code\\Powershell\\TestProject.dll", CallingConvention = CallingConvention.Cdecl)]
    #public static extern int MultiplyNumbers(int a, int b);
#"@

Add-Type -Namespace TestProjectV3 -Name NativeMethods -MemberDefinition @"
    [DllImport("E:\\TestProject.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int MultiplyNumbers(int a, int b);
"@

# Call it
$Result = [TestProjectV3.NativeMethods]::MultiplyNumbers(5, 9)
Write-Output "The result is $Result"