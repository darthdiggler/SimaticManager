# Create an Excel Application instance
$Excel = New-Object -ComObject Excel.Application
$Excel.Visible = $false

# Create a new workbook
$Workbook = $Excel.Workbooks.Add()
$Sheet = $Workbook.Worksheets.Item(1)
$Sheet.Cells.Item(1,1).Value = "Hello from PowerShell!"

# Save and quit
$Workbook.SaveAs("C:\Projects\VS_Code\Powershell\HMI_Testing\TestButt.xlsx")
$Excel.Quit()
