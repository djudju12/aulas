import 'package:flutter/material.dart';
import 'package:quiz_app/answer_button.dart';
import 'package:quiz_app/data/questions.dart';
import 'package:quiz_app/text_widget.dart';
import 'package:quiz_app/title_widget.dart';

class ResultScreen extends StatelessWidget {
  final List<String> choosenAnswers;
  const ResultScreen({super.key, required this.choosenAnswers});

  List<Map<String, Object>> getQuestionsSummary() {
    final List<Map<String, Object>> summary = [];

    for (var i = 0; i < choosenAnswers.length; i++) {
      summary.add({
        'question_index': i,
        'question': questions[i].text,
        'correct_answer': questions[i].answers[0],
        'user_answer': choosenAnswers[i],
      });
    }
    return summary;
  }

  @override
  Widget build(context) {
    return Column(
      mainAxisSize: MainAxisSize.min,
      children: [
        const TitleText("Dummy Text"),
        const TextWidget("Dummy Text"),
        AnswerButton(
          data: "Hiii",
          callback: () {},
        )
      ],
    );
  }
}
