class Question {
  final String text;
  final List<String> answers;

  const Question(this.text, this.answers);

  List<String> getShuffledAnswers() {
    final copiedList = List.of(answers);
    copiedList.shuffle();
    return copiedList;
  }
}
