# github 자동 업로드 코드
CURRENT_DIR = $(pwd)

echo ---------------------------
while [ ! -d ".git" ]; do
    cd ..
    echo "$(pwd)"
done
echo ---------------------------

git add .
git commit -m "Upload"
git push origin main

cd "$CURRENT_DIR"