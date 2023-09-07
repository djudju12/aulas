import 'package:flutter/material.dart';
import 'package:quiz_app/answer_button.dart';
import 'package:quiz_app/data/questions.dart';
import 'package:quiz_app/title_widget.dart';

class QuestionsWidget extends StatefulWidget {
  final void Function(String) onSelectAnswers;

  const QuestionsWidget({super.key, required this.onSelectAnswers});

  @override
  State<StatefulWidget> createState() {
    return _MakeQuestions();
  }
}

class _MakeQuestions extends State<QuestionsWidget> {
  int currentIndex = 0;
  void answerQuestion(String selectedAnswers) {
    widget.onSelectAnswers(selectedAnswers);
    setState(() {
      currentIndex++;
    });
  }

  @override
  Widget build(context) {
    return Container(
      margin: const EdgeInsets.all(40),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          TitleText(questions[currentIndex].text),
          const SizedBox(height: 20),
          ...questions[currentIndex].getShuffledAnswers().map((a) {
            return AnswerButton(
              data: a,
              callback: () {
                answerQuestion(a);
              },
            );
          })
        ],
      ),
    );
  }
}
