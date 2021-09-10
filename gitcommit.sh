echo "start git add"
git add .
echo "Enter commit message"
read commit_message
echo "start commit"
git commit -m "$commit_message Updated: `date +'%Y-%m-%d %H:%M:%S'`"
echo "push to master(default)"
git push
echo "successful!"