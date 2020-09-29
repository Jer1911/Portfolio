How to use:
-------------------------------------------------------------------------------
You must first be authenticated to follow this tutorial, (execute aws-mfa).

To provision the EKS cluster run this command:

time . deploy_eks.sh

To see the output, navigate to terraform-eks directory and run:

terraform output

To configure kubectl using the terraform output, note the region and name, and
use this command with the proper values:

aws eks --region YOUR-REGION update-kubeconfig --name YOUR-EKS-NAME

-------------------------------------------------------------------------------
To retrieve and apply metrics server and dashboard, run this command:

. create_dashboard.sh

-------------------------------------------------------------------------------
To make a dashboard proxy server, use command:

kubectl proxy

Keep the terminal open, and open a new terminal. In the new terminal, run these
commands (first command creates a token, second displays it):

. create_token.sh
. get_token.sh

navigate in browser to:

http://127.0.0.1:8001/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/

then select Token, and paste the token from the previous commands.

-------------------------------------------------------------------------------
Et voila, all done!

