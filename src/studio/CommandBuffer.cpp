
// enum class CommandType
// {
//     RemoveExpressionGroup,
//     RemoveExpression
// };

// struct RemoveExpressionGroupArgs
// {
//     int target;
// };

// struct RemoveExpressionArgs
// {
//     int groupTarget;
//     int expressionTarget;
// };

// struct Command
// {
//     CommandType type;
//     union
//     {
//         RemoveExpressionGroupArgs removeExpressionGroupArgs;
//         RemoveExpressionArgs removeExpressionArgs;
//     };
// };

// namespace CMD
// {
//     Command RemoveExpressionGroup(int target)
//     {
//         Command command = { 
//             .type = CommandType::RemoveExpressionGroup, 
//             .removeExpressionGroupArgs = { target }
//         };
//         return command;
//     }

//     Command RemoveExpression(int groupTarget, int expressionTarget)
//     {
//         Command command = { 
//             .type = CommandType::RemoveExpressionGroup, 
//             .removeExpressionArgs = { groupTarget, expressionTarget }
//         };
//         return command;
//     }
// }

// using CommandBuffer = std::vector<Command>;