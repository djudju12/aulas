import 'package:flutter/material.dart';
import 'package:quiz_app/answer_button.dart';
import 'package:quiz_app/data/questions.dart';
import 'package:quiz_app/models/question.dart';
import 'package:quiz_app/text_widget.dart';

class QuestionsWidget extends StatefulWidget {
  const QuestionsWidget({super.key});

  @override
  State<StatefulWidget> createState() {
    return _MakeQuestions();
  }
}

class _MakeQuestions extends State<QuestionsWidget> {
  int currentIndex = 0;
  void answerQuestion() {
    setState(() {
      if (currentIndex < (questions.length - 1)) {
        currentIndex++;
      }
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
          Text(
            questions[currentIndex].text,
            style: const TextStyle(
              color: Colors.white,
            ),
            textAlign: TextAlign.center,
          ),
          const SizedBox(height: 20),
          ...questions[currentIndex].getShuffledAnswers().map((a) {
            return AnswerButton(a, answerQuestion);
          })
        ],
      ),
    );
  }
}
